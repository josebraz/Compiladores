#ifndef UTIL_H
#define UTIL_H

#include "types.h"

void exporta(void *arvore);

void libera(void *arvore);

void free_node(node *n);

node *next_statement(node *parent);

#endif
