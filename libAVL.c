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

int calculaAltura(struct tNo *no) {
    int alturaEsq, alturaDir;
    if (no == NULL)
        return -1;

    alturaEsq = calculaAltura(no->esq);
    alturaDir = calculaAltura(no->dir);

    if (alturaEsq < alturaDir)
        return alturaDir + 1;
    return alturaEsq + 1;
}

struct tNo *rotEsquerda (struct tArvore *tree, struct tNo *no) {
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

    no->altura = calculaAltura(no);
    aux->altura = calculaAltura(aux);

    return aux;
}

struct tNo *rotDireita (struct tArvore *tree, struct tNo *no) {
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

    no->altura = calculaAltura(no);
    aux->altura = calculaAltura(aux);

    return aux;
}

struct tNo *min(struct tNo *no) {
    if (no->dir == NULL)
        return no;
    return min(no->dir);
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

int calculaEquilibrio(struct tNo *no) {
    return calculaAltura(no->esq) - calculaAltura(no->dir);
}

struct tNo *ajustaInsereArvore(struct tArvore *tree, struct tNo *no, int chave) {
    int equilibrio;

    no->altura = calculaAltura(no);
    equilibrio = calculaEquilibrio(no);

    if (equilibrio > 1) {
        if (no->esq != NULL && chave >= no->esq->chave)
            no->esq = rotEsquerda(tree, no->esq);
        return rotDireita(tree, no);
    }
    else if (equilibrio < -1) {
        if (no->dir != NULL && chave < no->dir->chave)
            no->dir = rotDireita(tree, no->dir);
        return rotEsquerda(tree, no);
    }

    return no;
}

struct tNo *adicionaChave(struct tArvore *tree, struct tNo *no, int chave) {
    if (no == NULL) {
        no = criaNo(chave);
        return no;
    }

    if (chave < no->chave) {
        no->esq = adicionaChave(tree, no->esq, chave);
        no->esq->pai = no;
    }
    else {
        no->dir = adicionaChave(tree, no->dir, chave);
        no->dir->pai = no;
    }

    return ajustaInsereArvore(tree, no, chave);
}

struct tNo *ajustaRemoveArvore(struct tArvore *tree, struct tNo *no) {
    struct tNo *p, *x, *y, *z;
    p = no;

    while (p != NULL) {
        p->altura = calculaAltura(p);

        if(calculaEquilibrio(p) <= -2 || calculaEquilibrio(p) >= 2) { //grandparent is unbalanced
            x = p;

            //taller child of x will be y
            if (x->esq->altura > x->dir->altura)
                y = x->esq;
            else
                y = x->dir;

            //taller child of y will be z
            if (y->esq->altura > y->dir->altura)
                z = y->esq;
            else if (y->esq->altura < y->dir->altura)
                z = y->dir;
            else //same altura go for single rotation
                if (y == x->esq)
                    z = y->esq;
                else
                    z = y->dir;

            //perform rotaions
            if (y == x->esq) {
                if (z == x->esq->esq) //case1
                    rotDireita(tree, x);
                else if (z == x->esq->dir) { //case 3
                    rotEsquerda(tree, y);
                    rotDireita(tree, x);
                }
            }
            else if (y == x->dir) {
                if (z == x->dir->dir) //case 2
                    rotEsquerda(tree, x);
                else if (z == x->dir->esq) { //case 4
                    rotDireita(tree, y);
                    rotEsquerda(tree, x);
                }
            }
        }
        p = p->pai;
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

void removeChaveAux(struct tArvore *tree, struct tNo *no) {
    struct tNo *sucessor, *aux;
    aux = no->pai;

    if (no->esq == NULL) {
        transplante(tree, no, no->dir);
        if (no->dir != NULL)
            aux = no->dir;
        free(no);
    }
    else if (no->dir == NULL) {
        transplante(tree, no, no->esq);
        if (no->esq != NULL)
            aux = no->esq;
        free(no);
    }
    else {
        sucessor = min(no->esq);
        if (sucessor->pai != no) {
            transplante(tree, sucessor, sucessor->esq);
            sucessor->esq = no->esq;
            sucessor->esq->pai = sucessor;
        }
        transplante(tree, no, sucessor);
        sucessor->dir = no->dir;
        sucessor->dir->pai = sucessor;
        if (sucessor != NULL)
            aux = sucessor;
        free(no);
    }

    ajustaRemoveArvore(tree, aux);
}

struct tNo *removeChave(struct tArvore *tree, int chave) {
    struct tNo *aux;
    
    aux = busca(tree->raiz, chave);
    removeChaveAux(tree, aux);

    return tree->raiz;
}

int quantidadeNos(struct tNo *no) {
    if (no == NULL)
        return 0;

    return 1 + quantidadeNos(no->esq) + quantidadeNos(no->dir);
}

void imprimeValores(struct tNo *no) {
    if (no == NULL)
        return;

    imprimeValores(no->esq);
    printf("%d,%d\n", no->chave, no->altura);
    imprimeValores(no->dir);
}

void inverteAlturas(struct tNo *no, int alt) {
    if (no == NULL)
        return;

    no->altura = alt;

    inverteAlturas(no->esq, alt + 1);
    inverteAlturas(no->dir, alt + 1);
}

void imprimeEmOrdem(struct tArvore *tree) {
    inverteAlturas(tree->raiz, 0);
    imprimeValores(tree->raiz);
}
