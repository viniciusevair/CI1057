struct tNo {
    int chave;
    int equilibrio;
    struct tNo *esq, *dir, *pai;
};

struct tArvore {
    struct tNo *raiz;
};

/* Cria uma árvore vazia. */
struct tArvore *criaArvore();

/* Destroi uma árvore e retorna NULL. */
struct tNo *destroiArvore(struct tArvore *tree);

struct tNo *adicionaChave(struct tArvore *tree, struct tNo *no, int chave, int *controle);

void removeChave(struct tArvore *tree, int chave);

/* Imprime os valores guardados na estrutura */
void imprimeEmOrdem(struct tNo *no);
