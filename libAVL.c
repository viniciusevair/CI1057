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

    return no;
}

struct tNo *adicionaChave(int chave) {
}

int tamanhoGalho(struct tNo *no) {
    if (no == NULL)
        return 0;

    return 1 + tamanhoGalho(no->esq) + tamanhoGalho(no->dir);
}

struct tNo *min(struct tNo *no) {
    if (no->esq == NULL)
        return no;
    return min(no->esq);
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

void imprimeEmOrdem(struct tNo *no) {
    if (no == NULL)
        return;

    imprimeEmOrdem(no->esq);
    printf("%d \n", no->chave);
    imprimeEmOrdem(no->dir);
}
