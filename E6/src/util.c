/*
Nomes: José Henrique da Silva Braz 
       Octavio do Amarante Arruda
Grupo: V
*/

#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "util.h"
#include "asp.h"
#include "instr_lst.h"
#include "semantic.h"
#include "hashmap.h"
#include "code_gen.h"
#include "arch_code_gen.h"

void print_tree_children(void *arvore) {
	int i;
    node *n = (node *) arvore;
    
    if (n == NULL) return;
    
    for (i = 0; i < n->size; i++) {
        if (n->nodes[i] != NULL) {
            printf("%p, %p\n", n, n->nodes[i]);
        }
    }
    if (n->next != NULL) {
        printf("%p, %p\n", n, n->next);
    }

    for (i = 0; i < n->size; i++) {
        print_tree_children(n->nodes[i]);
    }
    if (n->next != NULL) {
        print_tree_children(n->next);
    }
}

void print_tree_labels(void *arvore) {
	int i;
    node *n = (node *) arvore;
    
    if (n == NULL) return;
    
    printf("%p [label=\"%s\"];\n", n, n->label);
    
    for (i = 0; i < n->size; i++) {
        print_tree_labels(n->nodes[i]);
    }
    if (n->next != NULL) {
        print_tree_labels(n->next);
    }
}

void generate_dot_rec(void *arvore) {
    int i;
    node *n = (node *) arvore;
    
    if (n == NULL) return;
    
    printf("\t%ld [label=\"%s\" type=%d mark=%d]\n", (long)n, n->label, n->type, n->mark);
    
    for (i = 0; i < n->size; i++) {
        if (n->nodes[i] != NULL) {
            printf("\t%ld -> %ld\n", (long)n, (long)n->nodes[i]);
        }
    }
    if (n->next != NULL) {
        printf("\t%ld -> %ld\n", (long)n, (long)n->next);
    }

    for (i = 0; i < n->size; i++) {
        generate_dot_rec(n->nodes[i]);
    }
    if (n->next != NULL) {
        generate_dot_rec(n->next);
    }
}

void generate_dot(void *arvore) {
    printf("digraph {\n");
    generate_dot_rec(arvore);
    printf("}\n");
}

extern void exporta(void *arvore) {
    if (arvore != NULL) {
        instruction_entry_t *code = ((node*) arvore)->code;
        // printf("\n ------- ILOC CODE ---------- \n");
        // print_instr_lst(code);

        // code = instr_lst_remove_mark_interval(code, CODE_MARK_SAVE_REGS_START, CODE_MARK_SAVE_REGS_END);
        // code = instr_lst_remove_mark_interval(code, CODE_MARK_LOAD_REGS_START, CODE_MARK_LOAD_REGS_END);
        code = instr_lst_remove_mark_interval(code, CODE_MARK_INIT_CODE_START, CODE_MARK_INIT_CODE_END);

        // atualiza o ponteiro da primeira instrução do iloc porque 
        // ela pode ter mudado devido a remoção das marcações
        ((node*) arvore)->code = code;

        // printf("\n\n ------- ASSEMBLY CODE ----------\n");
        print_x86_64_assembly_code(code);
    }
}

void print_graph_node_colors(graph_t *graph, int *node_colors)
{
    printf("CORES:\n");

    for (int i = 0; i < graph->size ; i++) 
        printf("%d - %d\n", i, node_colors[i]);

    printf("\n");
}

void free_tree(node *n) {
    int i;

    if (n == NULL) return;
    for (i = 0; i < n->size; i++) {
        free_tree(n->nodes[i]);
    }
    if (n->next != NULL) {
        free_tree(n->next);
    }
    
    free_node(n);
}

void libera(void *arvore) 
{
    /* Only free ast that exists (empty program SIGSEGV) */
    if (arvore != NULL)
    {
        node *n = (node *) arvore;
        instr_lst_free(n->code);
        n->code = NULL;
        free_tree(arvore);
        free_scopes();
    }
}

