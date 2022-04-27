# Etapa 6

## Nomes:
- José Braz
- Octavio Arruda

## Grupo: 
- V

## Implementação
- 1ª Passagem geração ILOC
- 2ª Passagem otimização alocação registradores ILOC
  - Abordagem utilizando vida util da variável e grafos apresentada na aula "N12 A5 Alocação de Registradores"
- 3ª Passagem geração código x86_64 assembly a partir do código ILOC com reg. otimizado

### Geração de código assembly
- Mapeamento direto de instruções iloc para instruções de assembly
- O código assembly gerado deve ser capaz de ser utilizado por um montador para gerar um executável
- Referência: assembly x86_64 e gcc como montador
- Modificações na _main()_ liberadas
- Liberar a memória

### Funcionalidades necessárias: 
[ ] Implementar função _generateAsm()_
[ ] Gerar na saída padrão o segmento de dados e o segmento de código
[ ] Recomendação: Instrução ILOC 1:1 Instrução assembly
    - Mas não é regra!
    - Deve ser projetado e mapeado pelo grupo
[ ] Deve ser reconhecido e montado para um programa executável através do comando: gcc saida.s -o programa
    - Onde programa é um executável
    - GCC não pode "reclamar de nada"

### Conversões conhecidas
| -------------------- | ------------------- | ----------------------- |
| ILOC                 |   x86               |   Semantica             |
| -------------------- | ------------------- | ----------------------- |
| load r1 => r2        |   mov (%r1), %r2    |   r2 = Memoria(r1)      |
| loadAI r1, c => r2   |   mov c(%r1), %r2   |   r2 = Memoria(r1 + c)  |
| loadI c => r2        |   mov $c, %r2       |   r2 = c                |
| store r1 => r2       |   mov %r1, (%r2)    |   Memoria(r2) = r1      |
| storeAI r1 => r2, c  |   mov %r1, c(%r2)   |   Memoria(r2 + c) = r1  |
| i2i r1 => r2         |   mov %r1, %r2      |   r2 = r1               |
| add r1, r2 => r2     |   add %r1, %r2      |   r2 = r1 + r2          |
| addI r1, c => r1     |   add $c, %r1       |   r1 = c + r2           |
| sub r1, r2 => r2     |   sub %r1, %r2      |   r2 = r1 - r2          |
| subI r1, c => r1     |   sub $c, %r1       |   r1 = r1 - c           |
| rsubI r1, c => r1    |   sub %r1, $c       |   r1 = c - r1           |
| mult r1, r2 => r2    |   imul %r1, %r2     |   r2 = r1 * r2          |
| multI r1, c => r1    |   imul $c, %r1      |   r1 = r1 * c           |
| div r1, r2 => r2     |   idiv %r1, %r2     |   r2 = r1 / r2          |
| divI r1, c => r1     |   idiv $c, %r1      |   r1 = r1 / c           |
| rdivI r1, c => r1    |   idiv %r1, $c      |   r1 = c / r1           |
| and r1, r2 => r2     |   and %r1, %r2      |   r2 = r1 && r2         |
| andI r1, c => r1     |   and $c, %r1       |   r2 = r1 && c          |
| or r1, r2 => r2      |   or %r1, %r2       |   r2 = r1 || r2         |
| orI r1, c => r1      |   or $c, %r1        |   r2 = r1 || c          |
| xor r1, r2 => r2     |   xor %r1, %r2      |   r2 = r1 xor r2        |
| xorI r1, c => r1     |   xor $c, %r1       |   r2 = r1 xor c         |
| lshift r1, r2 => r2  |   sal %r1, %r2      |   r2 = r1 << r2         |
| lshiftI r1, c => r2  |   sal $c, %r2       |   r2 = r1 << c          |
| rshift r1, r2 => r2  |   sar %r1, %r2      |   r2 = r1 >> r2         |
| rshiftI r1, c => r2  |   sar $c, %r2       |   r2 = r1 >> c          |