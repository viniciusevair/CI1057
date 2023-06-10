#include <stdlib.h>
#include <stdio.h>
#include "libHASH.h"

int main(int argc, char *argv[]) {
    struct tabela_hash_t *tabela;
    char option;
    int chave;

    tabela = cria_tabela();

    while ((scanf(" %c %d", &option, &chave) == 2)) {
        if (option == 'i')
            insere_valor(tabela, chave);
        else if (option == 'r')
            remove_valor(tabela, chave);
    }

    escreve_ordenado(tabela);

    destroi_tabela(tabela);
    tabela = NULL;
    return 0;
}

