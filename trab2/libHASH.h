struct hashTable {
    int **T1;
    int **T2;
    int tam;
};

struct hashTable* criaTabela();

struct hashTable* destroiTabela();

int h1();

int h2();

void insereValor();

void buscaValor();

void removeValor();
