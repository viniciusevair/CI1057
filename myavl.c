#include <stdlib.h>
#include <stdio.h>
#include "libAVL.h"

int main(int argc, char *argv[]) {
    struct tArvore *tree;
    int qtd;
    char option;
    int chave;
    scanf("%d", &qtd);

    tree = criaArvore();

    while ((scanf(" %c %d", &option, &chave) == 2)) {
        if (option == 'i')
            tree->raiz = adicionaChave(tree, tree->raiz, chave);
        if (option == 'r')
            tree->raiz = removeChave(tree, chave);
    }

    imprimeEmOrdem(tree);
    destroiArvore(tree);

    return 0;
}
