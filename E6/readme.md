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