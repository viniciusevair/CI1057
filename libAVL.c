#include <stdlib.h>
#include <stdio.h>
#include "libAVL.h"

void zeraFamilia(struct tNo *no) {
    no->esq = NULL;
    no->dir = NULL;
    no->pai = NULL;
}

struct tArvore *criaArvore() {
    struct tArvore *tree;
    if (! (tree = malloc(sizeof(struct tNo)))) {
        fprintf (stderr, "Erro ao alocar memória");
        exit (1);
    }

    tree->raiz = NULL;

    return tree;
}

struct tNo *destroiArvore(struct tNo *no) {
    while (no->esq != NULL)
        destroiArvore(no->esq);
    while (no->dir != NULL)
        destroiArvore(no->dir);

    free(no);

    return NULL;
}

struct tNo *criaNo(int chave) {
    struct tNo *no;
    if (! (no = malloc(sizeof(struct tNo)))) {
        fprintf (stderr, "Erro ao alocar memória");
        exit (1);
    }

    no->chave = chave;
    no->esq = NULL;
    no->dir = NULL;
    no->pai = NULL;
    no->altura = 0;

    return no;
}

struct tNo *adicionaChave(struct tNo *raiz, int chave) {
    int i;

    return NULL;
}

int quantidadeNos(struct tNo *no) {
    if (no == NULL)
        return 0;

    return 1 + quantidadeNos(no->esq) + quantidadeNos(no->dir);
}

struct tNo *min(struct tNo *no) {
    if (no->esq == NULL)
        return no;
    return min(no->esq);
}

int altura(struct tNo *no) {
    return no->altura;
}

int comparaAltura (struct tNo *no) {
    if (no == NULL)
        return 0;
    return altura(no->esq) - altura(no->dir);
}

struct tNo *rotEsquerda (struct tArvore *tree, struct tNo *p) {
    struct tNo *q = p->dir;
    p->dir = q->esq;
    if (q->esq != NULL)
        q->esq->pai = p;
    q->pai = p->pai;
    if (p->pai == NULL)
        tree->raiz = q;
    else 
        if (p == p->pai->esq)
            p->pai->esq = q;
        else
            p->pai->dir = q;

    q->esq = p;
    p->pai = q;
    return q;
}

struct tNo *rotDireita (struct tArvore *tree, struct tNo *p) {
    struct tNo *q = p->esq;
    p->esq = q->dir;
    if (q->dir != NULL)
        q->dir->pai = p;
    q->pai = p->pai;
    if (p->pai == NULL)
        tree->raiz = q;
    else 
        if (p == p->pai->dir)
            p->pai->dir = q;
        else
            p->pai->esq = q;

    q->dir = p;
    p->pai = q;
    return q;
}

struct tNo *busca(struct tNo *no, int chave) {
    if (no == NULL)
        return NULL;
    if (no->chave == chave)
        return no;
    if (chave < no->chave)
        return busca(no->esq, chave);
    return busca(no->dir, chave);
}

void imprimeEmOrdem(struct tNo *no) {
    if (no == NULL)
        return;

    imprimeEmOrdem(no->esq);
    printf("%d \n", no->chave);
    imprimeEmOrdem(no->dir);
}
