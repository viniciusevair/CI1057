#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "libHASH.h"

#define HASHTAM 11

struct tabela_hash* cria_tabela() {
    struct tabela_hash *temp;
    if(! (temp = malloc(sizeof(struct tabela_hash)))) {
        fprintf(stderr, "Falha ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }
    temp->tam = HASHTAM;

    if(! (temp->T1 = calloc(temp->tam, sizeof(struct pos_hash*)))) {
        fprintf(stderr, "Falha ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }
    if(! (temp->T2 = calloc(temp->tam, sizeof(struct pos_hash*)))) {
        fprintf(stderr, "Falha ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < temp->tam; i++) {
        if(! (temp->T1[i] = malloc(sizeof(struct pos_hash)))) {
            fprintf(stderr, "Falha ao alocar memória.\n");
            exit(EXIT_FAILURE);
        }
        temp->T1[i]->estado = VAZIO;

        if(! (temp->T2[i] = malloc(sizeof(struct pos_hash)))) {
            fprintf(stderr, "Falha ao alocar memória.\n");
            exit(EXIT_FAILURE);
        }
        temp->T2[i]->estado = VAZIO;
    }

    return temp;
}

struct tabela_hash* destroi_tabela(struct tabela_hash *tabela) {
    for (int i = 0; i < tabela->tam; i++) {
        free(tabela->T1[i]);
        free(tabela->T2[i]);
    }

    free(tabela->T1);
    free(tabela->T2);
    free(tabela);

    return NULL;
}

int h1(int chave) {
    int pos = chave % HASHTAM;

    if(pos < 0)
        pos += HASHTAM;

    return pos;
}

int h2(int chave) {
    return floor(HASHTAM * (chave * 0.9 - floor(chave * 0.9)));
}

int insere_valor(struct tabela_hash *tabela, int chave) {
    int pos, aux;
    pos = h1(chave);

    if(tabela->T1[pos]->estado != OCUPADO) {
        tabela->T1[pos]->chave = chave;
        return 1;
    } else {
        aux = h2(chave);
        tabela->T2[aux]->chave = tabela->T1[pos]->chave;
        tabela->T1[pos]->chave = chave;
    }
}

void busca_valor(struct tabela_hash *tabela, int chave) {
}

void remove_valor(struct tabela_hash *tabela, int chave) {
}

void escreve_tabela(struct tabela_hash *tabela, int chave) {
}
