struct tNo {
    int chave;
    int altura;
    struct tNo *esq, *dir, *pai;
};

struct tArvore {
    struct tNo *raiz;
};

/* Cria uma árvore vazia. */
struct tArvore *criaArvore();

/* Destroi uma árvore e retorna NULL. */
struct tNo *destroiArvore(struct tNo *no);

struct tNo *adicionaChave(int chave);

/* Imprime os valores guardados na estrutura */
void imprimeEmOrdem(struct tNo *no);
