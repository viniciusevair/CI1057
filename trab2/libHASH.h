#ifndef __HASH
#define __HASH

enum estado_t {
    VAZIO,
    OCUPADO,
    EXCLUIDO,
};

struct pos_hash_t {
    int chave;
    enum estado_t estado;
};

struct tabela_hash_t {
    struct pos_hash_t *T;
    int tam;
};

struct tabela_hash_t* cria_tabela();

void destroi_tabela(struct tabela_hash_t *tabela);

int h1(int chave);

int h2(int chave);

void insere_valor(struct tabela_hash_t *tabela, int chave);

int busca_valor(struct tabela_hash_t *tabela, int chave);

void remove_valor(struct tabela_hash_t *tabela, int chave);

void escreve_ordenado(struct tabela_hash_t *tabela);

#endif
