
#include <stdio.h>
#include <string.h>

#include "../include/optimization.h"

extern int yyparse(void);
extern int yylex_destroy(void);

void *arvore = NULL;

void exporta(void *arvore);
void libera(void *arvore);

int main (int argc, char **argv)
{
  optimization_setup(argc, argv);
  int ret = yyparse();
  exporta(arvore);
  libera(arvore);
  arvore = NULL;  
  yylex_destroy(); 
  return ret;
}
