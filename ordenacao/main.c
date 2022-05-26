#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define TAMANHO 100000

// ORDENACAO POR INSERCAO (INSERTION SORT)

/*
    - Similar a ordenacao de cartas de baralho
    - Pega-se uma carta de cada vez e a coloca em seu devido lugar, sempre deixando
    as cartas da mão em ordem

    Performance:
    - Melhor caso: O(n)
    - Pior caso: O(n^2)
    - Eficiente p/ conjuntos pequenos de dados
    - Estavel: nao altera a ordem de dados iguais
    - Capaz de ordenar os dados a medida em que os recebe (tempo real)
*/
void insertionSort(int *vetor, int tamanhoVetor){
    int i, j, auxiliar;
    for(i = 1; i < tamanhoVetor; i++){
        auxiliar = vetor[i];
        for(j = i; (j > 0) && (auxiliar < vetor[j - 1]); j--)
            vetor[j] = vetor[j - 1];
        vetor[j] = auxiliar;
    }
}

// ORDENACAO POR TROCA DE PARTICOES (QUICK SORT)
/*
    - Ideia basica: DIVIDIR E CONQUISTAR
    - Um elemente é escolhido como pivo
    - Particiona (Funcao): os dados sao rearranjados (valores menores do que o pivo
sao colocados antes dele e os maiores, depois)
    - Recursivamente ordena as 2 particoes

    Performance:
    - Melhor caso: O(n log n)
    - Pior caso (raro): O(n^2)
    - Estavel: nao altera a ordem de dados iguais
    - Desvantagens: como escolher o pivo?
*/

int particiona(int *vetor, int inicio, int fim){
    int esq, dir, pivo, auxiliar;
    esq = inicio;
    dir = fim;
    pivo = vetor[inicio];

    while(esq < dir){
        // Avanca posicao da esquerda
        while(vetor[esq] <= pivo)
            esq++;
        // Recua posicao da direita
        while(vetor[dir] > pivo)
            dir--;
        // Troca esq e dir
        if(esq < dir){
            auxiliar = vetor[esq];
            vetor[esq] = vetor[dir];
            vetor[dir] = auxiliar;
        }
    }
    vetor[inicio] = vetor[dir];
    vetor[dir] = pivo;

    return dir;
}

void quickSort(int *vetor, int inicio, int fim){
    int pivo;
    if(fim > inicio){
        pivo = particiona(vetor, inicio, fim);
        quickSort(vetor, inicio, pivo - 1);
        quickSort(vetor, pivo + 1, fim);
    }
}

// ORDENACAO POR MISTURA (MERGE SORT)
/*
    - Ideia basica: dividir e conquistar
    - Divide, recursivamente, o conjunto de dados ate que cada subconjunto
possua 1 elemento.
    - Combina 2 subconjuntos de forma a obter 1 conjunto maior e ordenado
    - Esse processo se repete até que exista apenas 1 conjunto

    Performance:
    - Melhor caso: O(n log n)
    - Pior caso: O(n log n)
    - Estavel: nao altera a ordem de dados iguais
    - Desvantagens: recursivo e usa um vetor auxiliar durante a ordenacao
*/

void merge(int *vetor, int inicio, int meio, int fim){
    int *vetorTemporario, posicao1, posicao2, tamanho, i, j, k;
    int fim1 = 0, fim2 = 0;

    tamanho = fim - inicio + 1;
    posicao1 = inicio;
    posicao2 = meio + 1;
    vetorTemporario = (int *) malloc(tamanho*sizeof(int));

    if(vetorTemporario != NULL){
        for(i = 0; i < tamanho; i++){
            if(!fim1 && !fim2){
                // COMBINAR ORDENADO
                if(vetor[posicao1] < vetor[posicao2])
                    vetorTemporario[i] = vetor[posicao1++];
                else
                    vetorTemporario[i] = vetor[posicao2++];

                // VETOR ACABOU?
                if(posicao1 > meio)
                    fim1 = 1;
                if(posicao2 > fim)
                    fim2 = 1;
            }else{
                // COPIA O QUE SOBRAR
                if(!fim1)
                    vetorTemporario[i] = vetor[posicao1++];
                else
                    vetorTemporario[i] = vetor[posicao2++];
            }
        }
        // COPIAR DO AUXILIAR PARA O ORIGINAL
        for(j = 0, k = inicio; j < tamanho; j++, k++)
            vetor[k] = vetorTemporario[j];
    }
    free(vetorTemporario);
}

void mergeSort(int *vetor, int inicio, int fim){
    int meio;
    if(inicio < fim){
        meio = floor((inicio + fim) / 2);
        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio + 1, fim);
        merge(vetor, inicio, meio, fim);
    }
}

void randomizacaoVetor(int *vetor){
    int i;
    for(i = 0; i < TAMANHO; i++){
        vetor[i] = rand() % 100;
    }
}

int main()
{
    int vetorQuickSort[TAMANHO], vetorMergeSort[TAMANHO], vetorInsertionSort[TAMANHO];
    clock_t tempoMergeSort, tempoQuickSort, tempoInsertionSort;

    // Atribuicao de valores aleatorios ao vetor
    randomizacaoVetor(vetorInsertionSort);
    tempoInsertionSort = clock(); // Armazena o tempo inicial
    insertionSort(vetorInsertionSort, TAMANHO); // Realiza a ordenacao
    tempoInsertionSort = clock() - tempoInsertionSort; // Faz tempo final - inicial
    printf("O tempo gasto pelo InsertionSort foi: %lf segundos\n\n", ((double)tempoInsertionSort)/((CLOCKS_PER_SEC)));

    // Atribuicao de valores aleatorios ao vetor
    randomizacaoVetor(vetorQuickSort);
    tempoQuickSort = clock(); // Armazena o tempo inicial
    quickSort(vetorQuickSort, 0, TAMANHO - 1); // Realiza a ordenacao
    tempoQuickSort = clock() - tempoQuickSort; // Faz tempo final - inicial
    printf("O tempo gasto pelo QuickSort foi: %lf segundos\n\n", ((double)tempoQuickSort)/((CLOCKS_PER_SEC)));

    // Atribuicao de valores aleatorios ao vetor
    randomizacaoVetor(vetorMergeSort);
    tempoMergeSort = clock(); // Armazena o tempo inicial
    mergeSort(vetorMergeSort, 0, TAMANHO - 1); // Realiza a ordenacao
    tempoMergeSort = clock() - tempoMergeSort; // Faz tempo final - inicial
    printf("O tempo gasto pelo MergeSort foi: %lf segundos\n\n", ((double)tempoMergeSort)/((CLOCKS_PER_SEC)));

    return 0;
}
