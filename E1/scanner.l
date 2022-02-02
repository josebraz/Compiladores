%{

  // Para compilar o analizador
  // $ flex scanner.l
  // vai gerar o arquivos lex.yy.c
  // Agora podemos buildar o programa com a nossa main e linkando o lex
  // $ gcc lex.yy.c main.c -o analizador.out -lfl
  // Agora é só executar e correr pro abraço
  // $ ./analizador

  int get_line_number (void) {
  	return 1; // TODO
  }
%}

%%


