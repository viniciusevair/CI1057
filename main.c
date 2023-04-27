#include <stdlib.h>
#include <stdio.h>
#include "libAVL.h"

int main(int argc, char *argv[]) {
    struct tArvore *tree;
    int controle = 0;
    int qtd;
    scanf("%d", &qtd);

    tree = criaArvore();

    for (int i = 0; i < qtd; i++) {
        int aux;
        scanf("%d", &aux);
        tree->raiz = adicionaChave(tree, tree->raiz, aux, &controle);
    }

    imprimeEmOrdem(tree->raiz);
    destroiArvore(tree);

    return 0;
}
