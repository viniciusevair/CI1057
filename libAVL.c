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

struct tNo *destroiGalhos(struct tNo *no) {
    if(no->esq != NULL)
        destroiGalhos(no->esq);
    if(no->dir != NULL)
        destroiGalhos(no->dir);

    free(no);

    return NULL;
}

struct tNo *destroiArvore(struct tArvore *tree) {
    destroiGalhos(tree->raiz);
    free(tree);

    return NULL;
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

struct tNo *rotEsquerda (struct tArvore *tree, struct tNo *no) {
    printf("Rotacionando pra esquerda!\n");
    struct tNo *aux;
    aux = no->dir;
    no->dir = aux->esq;
    aux->pai = no->pai;
    if (aux->esq != NULL)
        aux->esq->pai = no;
    if (no->pai == NULL)
        tree->raiz = aux;
    else 
        if (no == no->pai->esq)
            no->pai->esq = aux;
        else
            no->pai->dir = aux;

    aux->esq = no;
    no->pai = aux;

    return aux;
}

struct tNo *rotDireita (struct tArvore *tree, struct tNo *no) {
    printf("Rotacionando pra direita!\n");
    struct tNo *aux;
    aux = no->esq;
    no->esq = aux->dir;
    aux->pai = no->pai;
    if (aux->dir != NULL)
        aux->dir->pai = no;
    if (no->pai == NULL)
        tree->raiz = aux;
    else 
        if (no == no->pai->dir)
            no->pai->dir = aux;
        else
            no->pai->esq = aux;

    aux->dir = no;
    no->pai = aux;

    return aux;
}

struct tNo *min(struct tNo *no) {
    if (no->esq == NULL)
        return no;
    return min(no->esq);
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

int altura(struct tNo *no) {
    int alturaEsq, alturaDir;
    if (no == NULL)
        return -1;

    alturaEsq = altura(no->esq);
    alturaDir = altura(no->dir);

    if (alturaEsq < alturaDir)
        return alturaDir + 1;
    return alturaEsq + 1;
}

struct tNo *ajustaArvore(struct tArvore *tree, struct tNo *no, int *controle) {
    struct tNo *aux;
    if (no->equilibrio == -2) {
        if (no->esq != NULL && no->esq->equilibrio > 0)
            no->esq = rotEsquerda(tree, no->esq);
        aux = rotDireita(tree, no);
    }
    else {
        if (no->dir != NULL && no->dir->equilibrio < 0)
            no->dir = rotDireita(tree, no->dir);
        aux = rotEsquerda(tree, no);
    }

    aux->equilibrio = 0;
    aux->esq->equilibrio = altura(aux->esq->dir) - altura(aux->esq->esq);
    aux->dir->equilibrio = altura(aux->dir->dir) - altura(aux->dir->esq);
    (*controle) = 0;

    return aux;
}

struct tNo *adicionaChave(struct tArvore *tree, struct tNo *no, int chave, int *controle) {
    if (no == NULL) {
        no = criaNo(chave);
        (*controle) = 1;
        return no;
    }

    if (chave < no->chave) {
        no->esq = adicionaChave(tree, no->esq, chave, controle);
        no->esq->pai = no;
        if (*controle)
            (no->equilibrio)--;
    }
    else {
        no->dir = adicionaChave(tree, no->dir, chave, controle);
        no->dir->pai = no;
        if (*controle)
            (no->equilibrio)++;
    }

    if (*controle) {
        if (no->equilibrio == 0)
            (*controle) = 0;
        if (no->equilibrio < -1 || no->equilibrio > 1)
            no = ajustaArvore(tree, no, controle);
    }

    return no;
}

void transplante(struct tArvore *tree, struct tNo *velho, struct tNo *novo) {
    if (velho == tree->raiz)
        tree->raiz = novo;
    else {
        if (velho == velho->pai->esq)
            velho->pai->esq = novo;
        else
            velho->pai->dir = novo;
    }

    if(novo != NULL) {
        novo->pai = velho->pai;
    }
}

void removeChave(struct tArvore *tree, int chave) {
    struct tNo *aux, *auxSucessor;
    aux = busca(tree->raiz, chave);

    if (aux->esq == NULL)
        transplante(tree, aux, aux->dir);
    else {
        if (aux->dir == NULL)
            transplante(tree, aux, aux->esq);
        else {
            auxSucessor = min(aux->dir);
            if (auxSucessor->pai != aux) {
                transplante(tree, auxSucessor, auxSucessor->dir);
                auxSucessor->dir = aux->dir;
                auxSucessor->dir->pai = auxSucessor;
            }
            transplante(tree, aux, novo);
            auxSucessor->esq = aux->esq;
            auxSucessor->esq->pai = auxSucessor;
        }
    }
}

int quantidadeNos(struct tNo *no) {
    if (no == NULL)
        return 0;

    return 1 + quantidadeNos(no->esq) + quantidadeNos(no->dir);
}

void imprimeValores(struct tNo *no, int alturaRaiz) {
    if (no == NULL)
        return;

    imprimeValores(no->esq, alturaRaiz);
    printf("%d,%d\n", no->chave, alturaRaiz - altura(no));
    imprimeValores(no->dir, alturaRaiz);
}

void imprimeEmOrdem(struct tNo *no) {
    int alturaRaiz = altura(no);

    imprimeValores(no, alturaRaiz);
}
