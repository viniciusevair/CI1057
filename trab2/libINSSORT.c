/*
 * Função simples que troca os valores guardados nos indices a e b do vetor.
 * Função auxiliar utilizada pelo Insertion Sort.
 */
void trocar(int vetor[], int a, int b) {
    int aux;
    aux = vetor[a];
    vetor[a] = vetor[b];
    vetor[b] = aux;
}

// Busca binária. Função auxiliar utilizada pelo Insertion Sort.
int buscar(int valor, int vetor[], int ini, int fim) {
    int meio;

    if(fim < ini)
        return ini - 1;

    meio = (ini + fim) >> 1;

    if(valor < vetor[meio]) {
        return buscar(valor, vetor, ini, meio - 1);
    }

    return buscar(valor, vetor, meio + 1, fim);
}

/*
 * Recebe um vetor indexado por [0..tam-1] com todos seus valores ordenados com
 * excessao do ultimo. Corrige a posição do último valor no vetor de maneira com
 * que o vetor fique completamente ordenado.
 * Função auxiliar utilizada pelo Insertion Sort.
 */ 
void ordena(int vetor[], int tam) {
    int posicao, i, ini, fim;
    ini = 0;
    fim = tam - 1;

    posicao = buscar(vetor[fim], vetor, ini, fim);
    for(i = fim; i > posicao + 1; i--)
        trocar(vetor, i, i - 1);
}

/*
 * Recebe um vetor indexado por [0..tam-1]. Ordena o vetor recebido.
 * Função auxiliar utilizada pelo Insertion Sort.
 */
void insertionSort(int vetor[], int tam) {
    if(tam <= 1)
        return;

    insertionSort(vetor, tam - 1);
    ordena(vetor, tam);
}
