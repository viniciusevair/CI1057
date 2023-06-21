/*
 * Biblioteca implementada pelo aluno Vinicius Evair da Silva para o Trabalho
 * Pratico 2, da disciplina de Algoritmos e Estrutura de Dados III (CI1057).
 */

#ifndef __HASH
#define __HASH

/*
 * Controle de estado das posições da HASH. O estado EXCLUIDO é necessário para
 * acessar a segunda tabela de dados.
 */
enum estado_t {
    VAZIO,
    OCUPADO,
    EXCLUIDO,
};

/*
 * Estrutura de posições da hash. Guarda uma chave, o estado da posição e
 * possívelmente um dado. Em especial, no caso deste trabalho, não há a
 * necessidade de guardar nenhum dado.
 */
struct pos_hash_t {
    int chave;
    enum estado_t estado;
    int pos;
};

/*
 * Estrutura da tabela hash, que guarda o vetor da tabela e o tamanho. O vetor
 * guarda o dobro de "tam", emulando assim duas tabelas (T1 e T2), mas guardadas
 * de maneira contigua na memória.
 */
struct tabela_hash_t {
    struct pos_hash_t **T;
    int tam;
};

// Inicializa a tabela, alocando memória para o vetor.
struct tabela_hash_t* cria_tabela();

// Libera toda a memória utilizada pela tabela.
void destroi_tabela(struct tabela_hash_t *tabela);

/*
 * Função hash para as primeiras onze posições da tabela (tabela T1). Utiliza o
 * resto da divisão do valor da chave por HASHTAM. Em caso de chave negativa,
 * devolve o resto POSITIVO da divisão por HASHTAM (i. e., soma-se tam ao
 * resultado).
 */
int h1(int chave);

/*
 * Função hash para as onze últimas posições da tabela (tabela T2).
 * Utiliza a expressão ⌊tam * (chave * 0.9 − ⌊chave * 0.9⌋)⌋ para calcular a
 * posição. Soma-se 11 ao resultado para utilizar as posições reservadas para
 * T2.
 */
int h2(int chave);

/*
 * Adiciona um novo valor na tabela hash. Nesta implementação, não são possíveis
 * chaves repetidas. Em caso de repetição das chaves, a chave mais nova é
 * descartada.
 */
void insere_valor(struct tabela_hash_t *tabela, int chave);

/*
 * Busca um valor na tabela. A busca pela chave é realizada primeiramente na T1
 * e, em caso de falha, busca na T2. Retorna a posição da chave em caso de
 * sucesso e retorna -1 em caso de falha. Se o valor de retorno positivo for
 * menor que onze, o dado se encontra na T1, caso contrário, o dado está na T2.
 */
struct pos_hash_t *busca_valor(struct tabela_hash_t *tabela, int chave);

/*
 * Remove um valor da tabela hash, liberando a posição.
 */
void remove_valor(struct tabela_hash_t *tabela, int chave);

/*
 * Imprime os valores guardados na tabela de maneira ordenada. A ordem da
 * impressão é crescente e de acordo com o valor da chave. Apesar do fato de que
 * nesta implementação não são aceitas chaves repetidas, ainda assim a função
 * garante que a hierarquia de ordenação em caso de repetições seja a chave,
 * seguido de qual tabela o dado está e por último a posição na tabela.
 */
void escreve_ordenado(struct tabela_hash_t *tabela);

#endif
