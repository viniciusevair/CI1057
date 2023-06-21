Relatório de Trabalho Prático 2 - Cuckoo Hashing
Vinicius Evair da Silva
ves22
GRR20221251
Graduando do Curso de Ciência da Computação

I. Introdução
    O presente relatório documenta o trabalho prático 2, da disciplina de Algoritmos
e Estrutura de Dados III (CI1057). O objetivo do trabalho é implementar uma
tabela hash de endereçamento aberto que utiliza o algoritmo de cuckoo hashing
para tratamento das chaves, porém, esta implementação não se preocupa com
rehashing ou redimencionamentos.

II. Da Estrutura
    Cada célula da tabela hash é uma estrutura que guarda o valor da chave, o
estado da célula e a posição na tabela. O valor de estado ajuda no gerenciamento
da inserção, busca e exclusão, enquanto o valor de posição serve apenas para
impressão ao fim da execução do programa.

III. Da Implementação
    Para a construção de ambas as tabelas hash foi utilizado um único vetor com
22 espaços, com os 11 primeiros sendo endereçados por h1 e os 11 últimos sendo
endereçados por h2, simulando assim, as tabelas T1 e T2. A escolha do uso de um
único vetor foi feita para simplificar a implementação de algumas das funções
deste trabalho.

III.a Da Inserção
III.b Da Exclusão
III.c Da Busca

III.d Da Impressão
    Como explicado nos comentários da biblioteca, foi utilizado para a impressão
ao fim da execuçao o algoritmo de ordenação Insertion Sort, uma vez que, caso
fosse possível a repetição dos dados, um algoritmo de ordenação estável
garantiria que os dados de T1 seriam impressos antes dos dados da T2
(respeitando assim a segunda regra de ordenação), e também garantiria que os
dados em posições menores seriam impressos antes dos dados de posições maiores
(respeitando a terceira regra de ordenação).

IV. Conclusão
