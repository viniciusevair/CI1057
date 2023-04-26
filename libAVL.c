#include <stdlib.h>
#include <stdio.h>
#include "libAVL.h"

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
    no->equilibrio = 0;

    return no;
}

struct tNo *rotEsquerda (struct tArvore *tree, struct tNo *p) {
    struct tNo *q = p->dir;
    p->dir = q->esq;
    q->pai = p->pai;
    if (q->esq != NULL)
        q->esq->pai = p;
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
    q->pai = p->pai;
    if (q->dir != NULL)
        q->dir->pai = p;
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

//struct tNo *ajustaArvore(struct tArvore *tree, struct tNo *no) {
//    struct tNo *aux;
//    if (no->equilibrio == -2) {
//        if (no->esq != NULL && no->esq->equilibrio > 0)
//            no->esq = rotEsquerda(tree, no);
//        aux = rotDireita(tree, no);
//    }
//}

struct tNo *adicionaChave(struct tNo *no, int chave) {
    if (no == NULL) {
        printf("Cheguei no fim da árvore. Vou por %d aqui.\n", chave);
        no = criaNo(chave);
        return no;
    }

    if (chave < no->chave) {
        printf("%d eh menor que %d, vou pra esquerda.\n", chave, no->chave);
        no->esq = adicionaChave(no->esq, chave);
        no->esq->pai = no;
        (no->equilibrio)--;
    }
    else {
        printf("%d eh menor que %d, vou pra direita.\n", chave, no->chave);
        no->dir = adicionaChave(no->dir, chave);
        no->dir->pai = no;
        (no->equilibrio)++;
    }

//    if (no->equilibrio == -2 || no->equilibrio == 2)
//        ajustaArvore(no);

    return no;
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
    int altEsq, altDir;

    if (no == NULL)
        return -1;

    altEsq = altura(no->esq);
    altDir = altura(no->dir);

    if (altDir < altEsq)
        return altEsq + 1;
    return altDir + 1;
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
    printf("%d ", no->chave);
    imprimeEmOrdem(no->dir);
}
