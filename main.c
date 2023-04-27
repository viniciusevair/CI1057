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
        char option;
        int chave;
        scanf("%c %d", &option, &chave);
        if (option == 'i') 
            tree->raiz = adicionaChave(tree, tree->raiz, aux, &controle);
        if (option == 'r') 
            tree->raiz = 
    }

    imprimeEmOrdem(tree->raiz);
    destroiArvore(tree);

    return 0;
}
