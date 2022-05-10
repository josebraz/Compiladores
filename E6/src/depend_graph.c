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

#define bool char
#define INVALID_COLOR -1

int get_live_interval(int reg, instruction_entry_t *instr, instruction_entry_t **start, instruction_entry_t **end) {
    instruction_entry_t *f_start = NULL, *f_end = NULL;
    instruction_entry_t *current = instr;
    while (current != NULL) {
        if (f_start == NULL) {
            // fase de procurar a primeira declaração
            if (current->entry->reg_result == reg) {
                f_start = current;
                // f_end = current;
            }
        } else {
            // fase de procurar o último uso
            if ((current->entry->op1 == reg && current->entry->op1_type == OT_REG) ||
                (current->entry->op2 == reg && current->entry->op2_type == OT_REG)) {
                    f_end = current;
            }
            if (current->entry->reg_result == reg) {
                break;
            }
        }
        current = current->next;
    }

    if (f_end == NULL) {
        // Só teve uma declaração, sem uso, então a vida 
        // dessa variável vai ser entendida como nenhuma
        *start = NULL;
        *end = NULL;
    } else {
        *start = f_start;
        *end = f_end;
    }

    return f_start != NULL && f_end != NULL;
}

int count_regs(instruction_entry_t *code) {
    int counter = 0;
    char* counted = (char *) calloc(1000, sizeof(char));

    instruction_entry_t *current = code;
    while (current != NULL) {
        instruction_t *instr = current->entry;
        if (instr->op1_type == OT_REG && instr->op1 >= 0 && counted[instr->op1] == 0) { // não contamos esse
            counted[instr->op1] = 1;
            counter++;
        }
        if (instr->op2_type == OT_REG && instr->op2 >= 0 && counted[instr->op2] == 0) { // não contamos esse
            counted[instr->op2] = 1;
            counter++;
        }
        if (instr->op3_type == OT_REG && instr->op3 >= 0 && counted[instr->op3] == 0) { // não contamos esse
            counted[instr->op3] = 1;
            counter++;
        }
        current = current->next;
    }
    free(counted);
    return counter;
}

int compute_all_reg_live(instruction_entry_t *code, var_live **lst_pointer) {
    int size = count_regs(code);
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

int compute_live_out(instruction_entry_t *code) {
    instruction_entry_t *current, *start, *end;
    int regs = count_regs(code);

    current = code;
    while (current != NULL) {
        current->entry->live_out_size = regs;
        memset(current->entry->live_out, 0, 100);
        current = current->next;
    }

    for (int reg = 0; reg < regs; reg++) {
        current = code;

        do {
            start = NULL;
            end = NULL;

            get_live_interval(reg, current, &start, &end);
            if (start != NULL) {
                while (current != start && current != NULL) {
                    current = current->next;
                }
                current->entry->live_out[reg] = 1;
                while (current != end && current != NULL) {
                    current = current->next;
                    current->entry->live_out[reg] = 1;
                }  
            } else {
                break;
            }
        } while (current != NULL);
    }

    return regs;
}

void print_graph(graph_t *graph) {
    printf("\t ");
    for (int i = 0; i < graph->size; i++) {
        printf("%d\t", i);
    }
    printf("\n");
    for (int i = 0; i < graph->size; i++) {
        printf("%d\t[", i);
        for (int j = 0; j <= i; j++) {
            printf("%d\t", graph->edges[i][j]);
        }
        printf("]\n");
    }
}

void free_depend_graph(graph_t *graph) {
    for (int i = 0; i < graph->size; i++) {
        free(graph->edges[i]);
    }

    free(graph);
}

graph_t *copy_depend_graph(graph_t *graph_source) {
    graph_t *new_graph = (graph_t *)calloc(1, sizeof(graph_t));
    new_graph->size = graph_source->size;
    new_graph->edges = (char **)calloc(graph_source->size, sizeof(char *));

    for(int i = 0; i < graph_source->size; i++) {
        new_graph->edges[i] = (char *) calloc(i+1, sizeof(char));
        
        for(int j = 0; j <= i; j++) {
            new_graph->edges[i][j] = graph_source->edges[i][j];
        }
    }

    return new_graph;
}

graph_t *generate_depend_graph(instruction_entry_t *code) {
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
            if (current_live.start != NULL && 
                    instr_lst_contain(current_live.start->next, current_live.end, current_instr->entry) == 1) 
            {
                for (int j = 0; j < i; j++) {
                    var_live other_live = live_lst[j];
                    if (other_live.start != NULL && 
                            instr_lst_contain(other_live.start->next, other_live.end, current_instr->entry) == 1) 
                    {
                        graph[i][j] = 1;
                    }
                }
                graph[i][i] = 1;
            }
        }
        current_instr = current_instr->next;
    }

    free(live_lst);
    live_lst = NULL;

    graph_t *new_graph = (graph_t *)calloc(1, sizeof(graph_t));
    new_graph->edges = graph;
    new_graph->size = size;

    return new_graph;
}

int count_neighborhood(int node, graph_t *graph) {
    int counter = 0;

    for (int j = 0; j <= node; j++) { // percorre a linha toda
        if (graph->edges[node][j] == 1) {
            counter++;
        }
    }
    for (int i = node; i < graph->size; i++) { // percorre a coluna toda
        if (graph->edges[i][node] == 1) {
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

/**
 * Encontra uma cor ainda não escolhida no vetor de cores neigh_colors
 * 
 * @param colors       total de cores
 * @param neigh_colors vetor de cores da vizinhaça
 * @return int         a cor escolhida ou #INVALID_COLOR se não tem nenhuma cor disponível
 */
int find_available_color(int colors, char *neigh_colors) {
    for (int i = 0; i < colors; i++) {
        if (neigh_colors[i] == 0) {
            return i;
        }
    }
    return INVALID_COLOR;
}

/**
 * Escolhe uma cor do nodo se ele ainda não não tiver nenhum cor
 * ou mantem a cor que o nodo já tem
 * 
 * @param node         número do nodo
 * @param colors       total de cores
 * @param g_colors     vetor de cores já atribuídas
 * @param neigh_colors vetor de cores da vizinhaça
 * @return int         a cor do nodo ou #INVALID_COLOR se não conseguiu dar uma cor nova
 */
int set_node_color(int node, int colors, int *g_colors, char *neigh_colors) {
    if (g_colors[node] != INVALID_COLOR) {
        return g_colors[node];
    }

    int new_color = find_available_color(colors, neigh_colors);
    if (new_color == -1) return -1;
    g_colors[node] = new_color;
    neigh_colors[new_color] = 1;

    return new_color;
}

/**
 * Popula o vetor neigh_colors com as cores da vizinhança de node
 * no neigh_colors o índice é a cor e o valor é 1 se a cor i está 
 * presente na vizinhança e 0 caso não esteja
 * 
 * @param node         número do nodo
 * @param size         tamanho do grafo
 * @param graph        grafo modelado como uma matriz
 * @param colors       total de cores
 * @param g_colors     vetor de cores já atribuídas
 * @param neigh_colors vetor de cores da vizinhaça
 */
void populate_neighborhood_colors(int node, graph_t *graph, const int *g_colors, char *neigh_colors) {
    for (int j = 0; j <= node; j++) { // percorre a linha toda
        if (graph->edges[node][j] == 1 && g_colors[j] != INVALID_COLOR) {
            neigh_colors[g_colors[j]] = 1;
        }
    }
    for (int i = node; i < graph->size; i++) { // percorre a coluna toda
        if (graph->edges[i][node] == 1 && g_colors[i] != INVALID_COLOR) {
            neigh_colors[g_colors[i]] = 1;
        }
    }
}

int try_color_graph(int colors, graph_t *graph, int **node_colors) {
    int colored_nodes_num = 0; // contador de quantos nodos tem cor
    int *g_node_color = (int *) calloc(graph->size, sizeof(int));      // indica qual a cor do nodo i
    char g_node_processed[graph->size]; // indica se o nodo i foi processado já
    bool neigh_colors[colors];   // 1 se a cor i já foi escolhida na vizinhança, 0 caso contrário

    graph_t *graph_copy = copy_depend_graph(graph);

    memset(g_node_color, INVALID_COLOR, graph->size * sizeof(int)); // marca todos como ainda sem cor
    memset(g_node_processed, 0, graph->size * sizeof(char));        // marca todos como não processados

    while (colored_nodes_num < graph->size) { // ainda falta nodos pra colorir
        memset(neigh_colors, 0, colors * sizeof(char));
        int enter_process = colored_nodes_num;
        int node = 0;

        while (node < graph->size && enter_process == colored_nodes_num) {
            if (g_node_processed[node] == 0) {
                int count = count_neighborhood(node, graph_copy);

                if (count < colors) { // podemos processar esse nodo
                    populate_neighborhood_colors(node, graph, g_node_color, neigh_colors);

                    // escolhe uma cor ainda não atribuída aos vizinhos se precisa
                    if (set_node_color(node, colors, g_node_color, neigh_colors) == INVALID_COLOR) 
                        goto failure;

                    // aloca uma cor para todos os visinhos ainda sem cor
                    for (int j = 0; j <= node; j++) { // percorre a linha toda
                        if (graph_copy->edges[node][j] == 1)
                            if (set_node_color(j, colors, g_node_color, neigh_colors) == INVALID_COLOR)
                                goto failure;
                        graph_copy->edges[node][j] = 0; // já remove o nodo
                    }
                    for (int i = node; i < graph->size; i++) { // percorre a coluna toda
                        if (graph_copy->edges[i][node] == 1)
                            if (set_node_color(i, colors, g_node_color, neigh_colors) == INVALID_COLOR)
                                goto failure;
                        graph_copy->edges[i][node] = 0; // já remove o nodo
                    }

                    g_node_processed[node] = 1;
                    colored_nodes_num++;
                }
            }
            node++;
        }

        if (node == graph->size  && colored_nodes_num < graph->size ) {
            // não conseguimos dar cor pra nenhum nodo nessa passagem, então 
            // não é possível colorir esse grafo com essa quantidade de cores
            goto failure;
        }
    }

    free_depend_graph(graph_copy);
    *node_colors = g_node_color;
    return 1;

failure:
    free_depend_graph(graph_copy);
    free(g_node_color);
    *node_colors = NULL;
    return 0;
}

