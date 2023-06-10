#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "libHASH.h"

#define HASHTAM 11

struct tabela_hash_t* cria_tabela() {
    struct tabela_hash_t *temp;
    if(! (temp = malloc(sizeof(struct tabela_hash_t)))) {
        fprintf(stderr, "Falha ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }
    temp->tam = HASHTAM * 2;

    if(! (temp->T = calloc(temp->tam, sizeof(struct pos_hash_t*)))) {
        fprintf(stderr, "Falha ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < temp->tam; i++) {
        temp->T[i].estado = VAZIO;
    }

    return temp;
}

void destroi_tabela(struct tabela_hash_t *tabela) {
    free(tabela->T);
    free(tabela);
}

int h1(int chave) {
    int pos_t1 = chave % HASHTAM;

    if(pos_t1 < 0)
        pos_t1 += HASHTAM;

    return pos_t1;
}

int h2(int chave) {
    return 11 + floor(HASHTAM * (chave * 0.9 - floor(chave * 0.9)));
}

void insere_valor(struct tabela_hash_t *tabela, int chave) {
    int pos_t1, pos_t2;
    pos_t1 = h1(chave);

    if(tabela->T[pos_t1].estado != OCUPADO) {
        tabela->T[pos_t1].chave = chave;
        tabela->T[pos_t1].estado = OCUPADO;
    } else {
        pos_t2 = h2(tabela->T[pos_t1].chave);
        tabela->T[pos_t2].chave = tabela->T[pos_t1].chave;
        tabela->T[pos_t2].estado = OCUPADO;
        tabela->T[pos_t1].chave = chave;
        tabela->T[pos_t1].estado = OCUPADO;
    }
}

int busca_valor(struct tabela_hash_t *tabela, int chave) {
    int pos_t1, pos_t2;
    pos_t1 = h1(chave);

    if(tabela->T[pos_t1].chave == chave) {
        return pos_t1;
    } else if (tabela->T[pos_t1].estado != VAZIO) {
        pos_t2 = h2(chave);
        if(tabela->T[pos_t2].chave == chave)
            return pos_t2;
    }

    return -1;
}

void remove_valor(struct tabela_hash_t *tabela, int chave) {
    int pos_t1, pos_t2;
    pos_t1 = h1(chave);

    if(tabela->T[pos_t1].chave == chave) {
        //arrumar os ponteiros depois
        tabela->T[pos_t1].estado = EXCLUIDO;
    } else {
        pos_t2 = h2(chave);
        if(tabela->T[pos_t2].chave == chave) {
            tabela->T[pos_t2].estado = EXCLUIDO;
        }
    }
}

void trocar(int vetor[], int a, int b) {
    int aux;
    aux = vetor[a];
    vetor[a] = vetor[b];
    vetor[b] = aux;
}

int buscar(int valor, int vetor[], int ini, int fim) {
    int meio;

    if(fim < ini)
        return ini - 1;

    meio = (ini + fim) >> 1;

    if(valor < vetor[meio]) {
        return buscar(valor, vetor, ini, meio - 1);
    }

    return buscar(valor, vetor, meio + 1, fim);
}

/*
 * Recebe um vetor indexado por [0..tam-1] com todos seus valores ordenados com
 * excessao do ultimo.
 * Ordena o vetor de maneira que fique completamente ordenado.
 * Retorna a quantidade de comparacoes feitas durante o processo.
 */ 
void insere(int vetor[], int tam) {
    int posicao, i, ini, fim;
    ini = 0;
    fim = tam - 1;

    posicao = buscar(vetor[fim], vetor, ini, fim);
    for(i = fim; i > posicao + 1; i--)
        trocar(vetor, i, i - 1);
}

/*
 * Recebe um vetor indexado por [0..tam-1].
 * Ordena o vetor recebido.
 * Retorna a quantidade de comparacoes feitas no processo.
 */
void insertionSort(int vetor[], int tam){	
    if(tam <= 1)
        return;

    insertionSort(vetor, tam - 1);
    insere(vetor, tam);
}

void escreve_ordenado(struct tabela_hash_t *tabela) {
    int pos_chave, count;
    int *aux;
    if(! (aux = calloc(HASHTAM * 2, sizeof(int)))) {
        fprintf(stderr, "Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }

    count = 0;
    for (int i = 0; i < tabela->tam; i++) {
        if(tabela->T[i].estado == OCUPADO) {
            aux[count] = tabela->T[i].chave;
            count++;
        }
    }

    insertionSort(aux, count);

    for (int i = 0; i < count; i++) {
        pos_chave = busca_valor(tabela, aux[i]);
        if(pos_chave < 11)
            printf("%d,T1,%d\n", aux[i], pos_chave);
        else
            printf("%d,T2,%d\n", aux[i], pos_chave % HASHTAM);
    }
}
