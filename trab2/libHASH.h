#ifndef __HASH
#define __HASH

enum estado_t {
    VAZIO,
    OCUPADO,
    EXCLUIDO,
};

struct pos_hash {
    int chave;
    enum estado_t estado;
};

struct tabela_hash {
    struct pos_hash **T1;
    struct pos_hash **T2;
    int tam;
};

struct tabela_hash* cria_tabela();

struct tabela_hash* destroi_tabela(struct tabela_hash *tabela);

int h1(int chave);

int h2(int chave);

int insere_valor(struct tabela_hash *tabela, int chave);

void busca_valor(struct tabela_hash *tabela, int chave);

void remove_valor(struct tabela_hash *tabela, int chave);

#endif
