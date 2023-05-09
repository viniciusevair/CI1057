#include <stdlib.h>
#include <stdio.h>
#include "libAVL.h"

int main(int argc, char *argv[]) {
    struct tArvore *tree;
    int qtd;
    scanf("%d", &qtd);

    tree = criaArvore();

    for (int i = 0; i < qtd; i++) {
        char option;
        int chave;
        scanf(" %c %d", &option, &chave);
        if (option == 'i')
            tree->raiz = adicionaChave(tree, tree->raiz, chave);
        if (option == 'r')
            tree->raiz = removeChave(tree, chave);
    }

    imprimeEmOrdem(tree);
    destroiArvore(tree);

    return 0;
}
