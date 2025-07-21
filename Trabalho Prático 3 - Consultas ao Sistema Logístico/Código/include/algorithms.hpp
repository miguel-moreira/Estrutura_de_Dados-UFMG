#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

// Arquivo que contém funções que venham a ser úteis durante a execução do problema.

#include "vector.hpp"

// Função merge, responsável por realmente ordenar o vetor, fazendo isto para as duas metades.
template<typename T>
void merge(vector<T>& array, int left, int mid, int right) {
    
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<T> Left(n1), Rig(n2);

    for (int i = 0; i < n1; i++) {
	    Left[i] = array[left + i];
    }
    for (int j = 0; j < n2; j++) {
	    Rig[j] = array[mid + 1 + j];
    }

    int i = 0, j = 0;
    int k = left;

    while (i < n1 and j < n2) {
	    if (Left[i] <= Rig[j]) {
	        array[k] = Left[i];
	        i++;
	    } else {
	        array[k] = Rig[j];
	        j++;
    	}
    	k++;
    }

    while (i < n1) {
	    array[k] = Left[i];
	    i++;
	    k++;
    }

    while (j < n2) {
	    array[k] = Rig[j];
	    j++;
	    k++;
    }
}

//Função mãe de "merge", responsável pelas chamadas recursivas e pela função "merge".
template<typename T>
void mergeSort(vector<T>& array, int left, int right) {    
    if (left >= right)
	return;

    int mid = (left + right) / 2;
    mergeSort(array, left, mid);
    mergeSort(array, mid + 1, right);
    merge(array, left, mid, right);
}

// Função simples e genérica para retornar o maior entre dois elementos.
template<typename T>
T max(T a, T b) {
    return (a > b) ? a : b;
}

#endif