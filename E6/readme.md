# Etapa 6

## Nomes:
- José Braz
- Octavio Arruda

## Grupo: 
- V

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