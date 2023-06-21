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
    A inserção usa a função h1 para checar a disponibilidade da célula em T1 e
insere a chave se o estado da célula for VAZIO. Se a celula em T1 estiver com o
estado EXCLUIDO, verifica se a chave já não está presente em T2 e só após a
negativa da verificação é que inclui a chave em T1. Em caso de
indisponibilidade, i. e., celula no estado OCUPADO, verifica se a célula ocupada
em T1 já contém a chave que está sendo inserida e, se for este o caso,
simplesmente termina a função, efetivamente descartando o dado novo.
    Sendo a chave a ser inserida diferente da já presente em T1, utiliza a
função h2 para verificar a disponibilidade em T2, preenchendo a célula se
possível. Em caso da célula estar no estado OCUPADO, não há a necessidade de
verificar se a chave presente é igual a que será inserida, uma vez que, dado
as especificações do trabalho, o dado será excluído de qualquer forma.

III.b Da Exclusão
    A exclusão usa h1 para verificar se a célula em T1 não está vazia e em
seguida, se possui a chave sendo excluida e, encontrando o dado, muda seu estado
para EXCLUIDO, ficando então a celula livre para ser usada novamente. Em caso da
chave em T1 ser diferente ou da célula possuir o estado EXLUIDO, repete o
processo em T2 utilizando h2.

III.c Da Busca
    Verifica se a celula em T1 possui a chave sendo buscada e se está no estado
OCUPADO. Em caso positivo, retorna a celula.
    Se a célula em T1 estiver no estado OCUPADO, mas com outra chave, ou estiver
no estado EXCLUIDO, repete o processo em T2 utilizando h2.

III.d Da Impressão
    Como explicado nos comentários da biblioteca, foi utilizado para a impressão
ao fim da execuçao o algoritmo de ordenação Insertion Sort, uma vez que, caso
fosse possível a repetição dos dados, um algoritmo de ordenação estável
garantiria que os dados de T1 seriam impressos antes dos dados da T2
(respeitando assim a segunda regra de ordenação), e também garantiria que os
dados em posições menores seriam impressos antes dos dados de posições maiores
(respeitando a terceira regra de ordenação).

IV. Considerações Finais
    Com esta implementação da Cuckoo Hash, mesmo com suas limitações foi 
possível experimentar o potencial da técnica de hashing, utilizada amplamente em
diversas áreas da computação.
    A biblioteca com a implementação funciona como o esperado, não falhando em
nenhum dos quatro testes disponibilizados pelo professor, e com nenhum vazamento
de memória.
