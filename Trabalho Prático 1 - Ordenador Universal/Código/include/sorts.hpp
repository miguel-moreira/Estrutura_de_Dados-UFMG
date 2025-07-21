#ifndef SORTS_HPP
#define SORTS_HPP

#include "vector.hpp"
#include "estatisticas.hpp"
#include <cstdlib> //srand48(seed)

// Código responsável por administrar os algoritmos de ordenação que serão usados e o algoritmo para randomizar o vetor

// Função que troca o valor de duas variáveis usando uma terceira 'temp', de temporária.
template<typename T>
void swap(T& a, T& b, estatisticas& estat) {
    try {
        T temp = a;
        a = b;
        b = temp;
        estat.incMovimentacoes(3);
    } catch (...) {
        fprintf(stderr, "Erro no swap de elementos.\n");
    }
}

// Função resgatada da PA1 para determinar qual dos elementos é o médio em relação aos outros.
template<typename T>
T mediana (T& a, T& b, T& c) {
    try {
        if ((a <= b) && (b <= c)) return b;  // a b c
        if ((a <= c) && (c <= b)) return c;  // a c b
        if ((b <= a) && (a <= c)) return a;  // b a c
        if ((b <= c) && (c <= a)) return c;  // b c a
        if ((c <= a) && (a <= b)) return a;  // c a b
        return b;                            // c b a
    } catch (...) {
	    fprintf(stderr, "Erro no cálculo da mediana.\n");
    }
    return a;
}

// Função adaptada da PA1, muito usada em vetores quase-ordenados ou pequenos.
template<typename T>
void insertionSort(vector<T>& vetor, int esquerda, int direita, estatisticas& estat) {
    estat.incChamadas();
    try {
        for (int i = esquerda + 1; i <= direita; ++i) {
            T chave = vetor[i];
            estat.incMovimentacoes();
            int j = i - 1;
            estat.incComparacoes();
            while (j >= 0 and chave < vetor[j]) {
                estat.incComparacoes();
                vetor[j+1] = vetor[j];
                estat.incMovimentacoes();
                j--;
            }
            vetor[j+1] = chave;
            estat.incMovimentacoes();
        }
    } catch (...) {
        fprintf(stderr, "Erro durante o insertionSort.\n");
    }
}

// Função interna do QuickSort, responsável por dividir os lados que serão chamados recursivamente.
template<typename T>
void partition(vector<T>& vetor, int esquerda, int direita, int* i, int* j, estatisticas& estat) {
   estat.incChamadas();
    try {
        *i = esquerda;
        *j = direita;

        int meio = (esquerda + direita) / 2;
        T pivot = mediana(vetor[esquerda], vetor[meio], vetor[direita]);

        do {
            estat.incComparacoes(2);
            while (vetor[*i] < pivot) {
                (*i)++;
                estat.incComparacoes();
            }
            while (vetor[*j] > pivot) {
                (*j)--;
                estat.incComparacoes();
            }
            if (*i <= *j) {
                swap(vetor[*i], vetor[*j], estat);
                (*i)++;
                (*j)--;
            }
        } while (*i <= *j);
    } catch (...) {
        fprintf(stderr, "Erro durante o partition do quickSort.\n");
    }
}

// Função adaptada da PA1 usada para o sort de grandes vetores em pouco tempo.
template<typename T>
void quickSort(vector<T>& vetor, int esquerda, int direita, estatisticas& estat, int minTamParticao) {
    estat.incChamadas();
    try {
        int i, j;
        partition(vetor, esquerda, direita, &i, &j, estat);

        if (esquerda < j and j - esquerda < minTamParticao)
            insertionSort(vetor, esquerda, j, estat);
        else if (j > esquerda)
            quickSort(vetor, esquerda, j, estat, minTamParticao);

        if (direita > i and direita - i < minTamParticao)
            insertionSort(vetor, i, direita, estat);
        else if (direita > i)
            quickSort(vetor, i, direita, estat, minTamParticao);
    } catch (...) {
        fprintf(stderr, "Erro durante o quickSort.\n");
    }
}

// Função dada no enunciado para randomizar os elementos do vetor mantendo um número 'numShuffle' de quebras.
template<typename T>
int shuffleVector(vector<T>& vetor, int numShuffle, int seed) {
     try {
        srand48(seed);
        int p1 = 0, p2 = 0; 
	T temp;
        for (int t = 0; t < numShuffle; t++) {
            while (p1 == p2) {
                p1 = (int)(drand48() * vetor.tamanho());
                p2 = (int)(drand48() * vetor.tamanho());
            }
            temp = vetor[p1];
            vetor[p1] = vetor[p2];
            vetor[p2] = temp;
            p1 = p2 = 0;
        }
        return 0;
    } catch (...) {
        fprintf(stderr, "Erro no shuffleVector.\n");
        return -1;
    }
}

#endif