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

/* Funcao auxiliar para recursivamente destruir todos os nos da arvore. */
struct tNo *destroiGalhos(struct tNo *no) {
    if(no->esq != NULL)
        destroiGalhos(no->esq);
    if(no->dir != NULL)
        destroiGalhos(no->dir);

    free(no);

    return NULL;
}

struct tNo *destroiArvore(struct tArvore *tree) {
    if (tree->raiz != NULL)
        destroiGalhos(tree->raiz);
    free(tree);

    return NULL;
}

/*
 * Recebe como entrada uma chave a ser buscada, e um no como ponto de partida.
 * Retorna um ponteiro para o no da chave em caso de sucesso e NULL caso a chave
 * nao exista na arvore.
 */
struct tNo *busca(struct tNo *no, int chave) {
    if (no == NULL)
        return NULL;
    if (no->chave == chave)
        return no;
    if (chave < no->chave)
        return busca(no->esq, chave);
    return busca(no->dir, chave);
}

/* Refaz o calculo da altura de um no e retorna o valor como um inteiro. */
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

/*
 * Reorganiza os nos da arvore fazendo uma rotacao para a esquerda.
 * Diminui em 1 a altura da subarvore no processo e, por conta disso, recalcula
 * a altura dos nos envolvidos na rotacao.
 * Retorna um ponteiro para a nova raiz da subarvore.
 */
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

/*
 * Reorganiza os nos da arvore fazendo uma rotacao para a direita.
 * Diminui em 1 a altura da subarvore no processo e, por conta disso, recalcula
 * a altura dos nos envolvidos na rotacaoo.
 * Retorna um ponteiro para a nova raiz da subarvore.
 */
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

/* 
 * Recebe como parametro um no. Retorna um ponteiro para o no com a chave
 * antecessora a chave do no.
 */
struct tNo *encontraAntecessor(struct tNo *no) {
    if (no->dir == NULL)
        return no;
    return encontraAntecessor(no->dir);
}

/* 
 * Recebe como parametro um inteiro. Cria um no com todos os valores zerados,
 * com excessao da chave. Retorna um ponteiro para o no. 
 */
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

/*
 * Recebe como entrada um no. Retorna um inteiro que representa o equilibrio do
 * no. Valores positivos indicam que a subarvore do filho esquerdo e maior que a
 * subarvore do filho direito, e valores negativos indicam o inverso.
 */
int calculaEquilibrio(struct tNo *no) {
    return calculaAltura(no->esq) - calculaAltura(no->dir);
}

/*
 * Funcao auxiliar que verifica o equilibrio do no (menor que -2 ou maior que 2
 * indicam desequilibrio) e faz as rotacoes necessarias para corrigir o
 * equilibrio.
 */
struct tNo *ajustaInsereArvore(struct tArvore *tree, struct tNo *no) {
    int equilibrio;

    equilibrio = calculaEquilibrio(no);

    if (equilibrio > 1) {
        if (calculaEquilibrio(no->esq) < 0)
            no->esq = rotEsquerda(tree, no->esq);
        no = rotDireita(tree, no);
    }
    else if (equilibrio < -1) {
        if (calculaEquilibrio(no->dir) > 0)
            no->dir = rotDireita(tree, no->dir);
        no = rotEsquerda(tree, no);
    }

    return no;
}

/*
 * Recebe como parametro uma chave, uma arvore e um no. Cria e adiciona um no
 * com a chave na arvore especificada, ordenando a partir do no especificado.
 * Retorna um ponteiro para o 
 */
struct tNo *adicionaChaveAux(struct tArvore *tree, struct tNo *no, int chave) {
    if (no == NULL) {
        no = criaNo(chave);
        return no;
    }

    if (chave < no->chave) {
        no->esq = adicionaChaveAux(tree, no->esq, chave);
        no->esq->pai = no;
    }
    else {
        no->dir = adicionaChaveAux(tree, no->dir, chave);
        no->dir->pai = no;
    }

    return ajustaInsereArvore(tree, no);
}

/* Wrapper para a funcao que adiciona chave */
struct tNo *adicionaChave(struct tArvore *tree, int chave) {
    return adicionaChaveAux(tree, tree->raiz, chave);
}

/*
 * Funcao auxiliar que verifica o equilibrio do no (menor que -2 ou maior que 2
 * indicam desequilibrio) e faz as rotacoes necessarias para corrigir o
 * equilibrio. Recalcula recursivamente o equilibrio ate a raiz.
 */
struct tNo *ajustaRemoveArvore(struct tArvore *tree, struct tNo *no) {
    int equilibrio;

    if (no == NULL)
        return no;

    equilibrio = calculaEquilibrio(no);

    if (equilibrio > 1) {
        if (calculaEquilibrio(no->esq) < 0)
            no->esq = rotEsquerda(tree, no->esq);
        no = rotDireita(tree, no);
    }
    else if (equilibrio < -1) {
        if (calculaEquilibrio(no->dir) > 0)
            no->dir = rotDireita(tree, no->dir);
        no = rotEsquerda(tree, no);
    }

    return ajustaRemoveArvore(tree, no->pai);
}

/* Coloca um novo no na posicao de um no antigo. */
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

/*
 * Faz o transplante nos nodos corretamente a depender dos tres casos possiveis.
 */
void removeChaveAux(struct tArvore *tree, struct tNo *no) {
    struct tNo *antecessor, *aux;
    aux = no->pai;

    /* Caso em que o nodo tem apenas o filho da direita. */
    if (no->esq == NULL) {
        transplante(tree, no, no->dir);

        if (no->dir != NULL)
            aux = no->dir;

        free(no);
    }
    /* Caso o no tenha apenas o filho da esquerda ou nenhum filho. */
    else if (no->dir == NULL) {
        transplante(tree, no, no->esq);

        if (no->esq != NULL)
            aux = no->esq;

        free(no); //No caso de nenhum filho, simplesmente deleta o no.
    }
    /* Caso o no tenha os dois filhos */
    else {
        antecessor = encontraAntecessor(no->esq);

        /* 
         * Se o antecessor nao estiver diretamente conectado no no a ser
         * removido, e necessario corrigir os ponteiros para o filho esquerdo do
         * no.
         */
        if (antecessor->pai != no) {
            transplante(tree, antecessor, antecessor->esq);
            antecessor->esq = no->esq;
            antecessor->esq->pai = antecessor;
        }

        transplante(tree, no, antecessor);

        antecessor->dir = no->dir;
        antecessor->dir->pai = antecessor;

        if (antecessor != NULL)
            aux = antecessor;
        free(no);
    }

    ajustaRemoveArvore(tree, aux);
}

struct tNo *removeChave(struct tArvore *tree, int chave) {
    struct tNo *aux;

    if (! (aux = busca(tree->raiz, chave)))
        return NULL;

    removeChaveAux(tree, aux);

    return tree->raiz;
}

/* Conta quantos nos possuem na subarvore que comeca em no. */
int quantidadeNos(struct tNo *no) {
    if (no == NULL)
        return 0;

    return 1 + quantidadeNos(no->esq) + quantidadeNos(no->dir);
}

/* Caminha recursivamente e imprime a chave e nivel de cada no emordem. */
void imprimeValores(struct tNo *no, int nivel) {
    if (no == NULL)
        return;

    imprimeValores(no->esq, nivel + 1);
    printf("%d,%d\n", no->chave, nivel);
    imprimeValores(no->dir, nivel + 1);
}

/* Wrapper para a funcao que imprime as chaves e os niveis dos nos. */
void imprimeEmOrdem(struct tArvore *tree) {
    imprimeValores(tree->raiz, 0);
}
