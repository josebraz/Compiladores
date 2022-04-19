/*
Nomes: José Henrique da Silva Braz 
       Octavio do Amarante Arruda
Grupo: V
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "depend_graph.h"
#include "instr_lst.h"
#include "code_gen.h"
#include "types.h"

#define INVALID_COLOR -1

typedef struct __var_live {
    int var;
    instruction_entry_t *start;
    instruction_entry_t *end;
} var_live;

int get_live_interval(int reg, instruction_entry_t *instr, instruction_entry_t **start, instruction_entry_t **end) {
    instruction_entry_t *f_start = NULL, *f_end = NULL;
    instruction_entry_t *current = instr;
    while (current != NULL) {
        if (f_start == NULL) {
            // fase de procurar a primeira declaração
            if (current->entry->op3 == reg && current->entry->op3_type == OT_REG) {
                f_start = current;
                f_end = current;
            }
        } else {
            // fase de procurar o último uso
            if ((current->entry->op1 == reg && current->entry->op1_type == OT_REG) ||
                (current->entry->op2 == reg && current->entry->op2_type == OT_REG)) {
                    f_end = current;
            }
        }
        current = current->next;
    }
    *start = f_start;
    *end = f_end;

    return f_start != NULL && f_end != NULL;
}

int compute_all_reg_live(instruction_entry_t *code, var_live **lst_pointer) {
    int size = next_reg();
    var_live *live_lst = (var_live *) calloc(size, sizeof(var_live));

    if (live_lst == NULL) {
        exit(1);
    }

    for (int reg = 0; reg < size; reg++) {
        live_lst[reg].var = reg;
        get_live_interval(reg, code, &(live_lst[reg].start), &(live_lst[reg].end));
    }

    *lst_pointer = live_lst;
    return size;
}

void print_graph(int size, const char **graph) {
    printf("\t ");
    for (int i = 0; i < size; i++) {
        printf("%d\t", i);
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf("%d\t[", i);
        for (int j = 0; j <= i; j++) {
            printf("%d\t", graph[i][j]);
        }
        printf("]\n");
    }
}

void free_depend_graph(int size, char **graph) {
    for(int i = 0; i < size; i++) {
        free(graph[i]);
    }
    free(graph);
}

void copy_depend_graph(int size, const char **graph_src, char ***graph_dest) {
    char **graph = (char **) calloc(size, sizeof(char *));
    for(int i = 0; i < size; i++) {
        graph[i] = (char *) calloc(i+1, sizeof(char));
        for(int j = 0; j <= i; j++) {
            graph[i][j] = graph_src[i][j];
        }
    }
    *graph_dest = graph;
}

int generate_depend_graph(instruction_entry_t *code, char ***graph_result) {
    var_live *live_lst;
    int size = compute_all_reg_live(code, &live_lst);

    char **graph = (char **) calloc(size, sizeof(char *));
    for(int i = 0; i < size; i++) {
        graph[i] = (char *) calloc(i+1, sizeof(char));
    }

    instruction_entry_t *current_instr = code;
    while (current_instr != NULL) {
        for (int i = 0; i < size; i++) {
            var_live current_live = live_lst[i];
            if (instr_lst_contain(current_live.start, current_live.end, current_instr->entry) == 1) {
                for (int j = 0; j < i; j++) {
                    var_live other_live = live_lst[j];
                    if (instr_lst_contain(other_live.start, other_live.end, current_instr->entry) == 1) {
                        graph[i][j] = 1;
                    }
                }
            }
        }
        current_instr = current_instr->next;
    }

    free(live_lst);
    live_lst = NULL;

    *graph_result = graph;
    return size;
}

int count_neighborhood(int node, int size, char **graph) {
    int counter = 0;
    for (int j = 0; j <= node; j++) { // percorre a linha toda
        if (graph[node][j] == 1) {
            counter++;
        }
    }
    for (int i = node; i < size; i++) { // percorre a coluna toda
        if (graph[i][node] == 1) {
            counter++;
        }
    }
    return counter;
}

void remove_node(int node, int size, char **graph) {
    for (int j = 0; j <= node; j++) { // percorre a linha toda
        graph[node][j] = 0;
    }
    for (int i = node; i < size; i++) { // percorre a coluna toda
        graph[i][node] = 0;
    }
}

int find_available_color(int colors, char *temp_colors) {
    for (int i = 0; i < colors; i++) {
        if (temp_colors[i] == 0) {
            return i;
        }
    }
    return -1;
}

int set_node_color(int node, int colors, int *g_colors, char *temp_colors) {
    if (g_colors[node] != INVALID_COLOR) {
        return g_colors[node];
    }

    int new_color = find_available_color(colors, temp_colors);
    if (new_color == -1) return -1;
    g_colors[node] = new_color;
    temp_colors[new_color] = 1;

    return new_color;
}

void populate_neighborhood_colors(int node, int size, const char **graph, const int *g_colors, char *temp_colors) {
    for (int j = 0; j <= node; j++) { // percorre a linha toda
        if (graph[node][j] == 1 && g_colors[j] != INVALID_COLOR) {
            temp_colors[g_colors[j]] = 1;
        }
    }
    for (int i = node; i < size; i++) { // percorre a coluna toda
        if (graph[i][node] == 1 && g_colors[i] != INVALID_COLOR) {
            temp_colors[g_colors[i]] = 1;
        }
    }
}

int try_color_graph(int colors, int size, const char **graph_original) {
    int process = 0;          // contador de quantos nodos tem cor
    char **graph;             // cópia do grafo
    int g_colors[size];       // indica qual a cor do nodo i
    char g_process[size];     // indica se o nodo i foi processado já
    char temp_colors[colors]; // 1 se a cor i já foi escolhida na vizinhança, 0 caso contrário

    copy_depend_graph(size, graph_original, &graph);
    memset(g_colors, INVALID_COLOR, size * sizeof(int)); // marca todos como ainda sem cor
    memset(g_process, 0, size * sizeof(char));           // marca todos como não processados

    while (process < size) {
        memset(temp_colors, 0, colors * sizeof(char));
        int enter_process = process;
        int node = 0;
        while (node < size && enter_process == process) {
            if (g_process[node] == 0) {
                int count = count_neighborhood(node, size, graph);
                if (count < colors) { // podemos processar esse nodo
                    populate_neighborhood_colors(node, size, graph_original, g_colors, temp_colors);

                    // escolhe uma cor ainda não atribuída aos vizinhos se precisa
                    if (set_node_color(node, colors, g_colors, temp_colors) == INVALID_COLOR) 
                        goto fail;

                    // aloca uma cor para todos os visinhos ainda sem cor
                    for (int j = 0; j <= node; j++) { // percorre a linha toda
                        if (graph[node][j] == 1)
                            if (set_node_color(j, colors, g_colors, temp_colors) == INVALID_COLOR)
                                goto fail;
                        graph[node][j] = 0; // já remove o nodo
                    }
                    for (int i = node; i < size; i++) { // percorre a coluna toda
                        if (graph[i][node] == 1)
                            if (set_node_color(i, colors, g_colors, temp_colors) == INVALID_COLOR)
                                goto fail;
                        graph[i][node] = 0; // já remove o nodo
                    }

                    g_process[node] = 1;
                    process++;
                }
            }
            node++;
        }

        if (node == size && process < size) {
            // não conseguimos dar cor pra nenhum nodo nessa passagem, então 
            // não é possível colorir esse grafo com essa quantidade de cores
            goto fail;
        }
    }

    printf("CORES:\n");
    for (int i = 0; i < size; i++) {
        printf("%d - %d\n", i, g_colors[i]);
    }
    printf("\n");

    free_depend_graph(size, graph);
    return 1;

fail:
    printf("FAIL");
    free_depend_graph(size, graph);
    return 0;
}

