struct tNo {
    int chave;
    int altura;
    struct tNo *esq, *dir, *pai;
};

struct tArvore {
    struct tNo *raiz;
};

/*
 * Cria e aloca espaco para uma arvore vazia. A responsabilidade por desalocar a
 * memoria utilizada e de quem chamou a funcao.
 */
struct tArvore *criaArvore();

/*
 * Desaloca recursivamente a memoria de todos os nos e em seguida a da arvore.
 * sempre retorna NULL.
 */
struct tNo *destroiArvore(struct tArvore *tree);

/*
 * Adiciona um novo no na arvore. Nesta implementacao, sao permitidas repeticoes
 * de chaves, com as chaves repetidas ficando para a direita da chave de mesmo
 * valor. Retorna um ponteiro para raiz da subarvore.
 */
struct tNo *adicionaChave(struct tArvore *tree, struct tNo *no, int chave);

/*
 * Remove um no da arvore. Retorna a raiz da arvore em caso de sucesso e NULL em
 * caso de falha, i.e., caso a chave a ser removida nao exista na arvore.
 */
struct tNo *removeChave(struct tArvore *tree, int chave);

/* Imprime os valores guardados na estrutura */
void imprimeEmOrdem(struct tArvore *tree);
