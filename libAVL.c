#include <stdlib.h>
#include <stdio.h>

struct tNo {
    char valor;
    int altura;
    struct tNo *esq, *dir, *pai;
};

struct tNo *min(struct tNo *no) {
    if (no->esq == NULL)
        return no;
    return min(no->esq);
}

struct tNo *rotEsquerda (struct tNo *p) {
    struct tNo *q = p->dir;
    p->dir = q->esq;
    q->pai = p->pai;
    p->pai = q;
    if (q->esq != NULL)
        q->esq->pai = p;

    q->esq = p;
    return q;
}

struct tNo *rotDireita (struct tNo *p) {
    struct tNo *q = p->esq;
    p->esq = q->dir;
    q->pai = p->pai;
    p->pai = q;
    if (q->dir != NULL)
        q->dir->pai = p;

    q->dir = p;
    return q;
}
