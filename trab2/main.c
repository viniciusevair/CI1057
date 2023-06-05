#include <stdlib.h>
#include <stdio.h>
#include "libHASH.h"

int main(int argc, char *argv[]) {
    int qtd;
    char option;
    int chave;
    scanf("%d", &qtd);

    while ((scanf(" %c %d", &option, &chave) == 2)) {
        if (option == 'i')
        else if (option == 'r')
    }

    return 0;
}

