#include "heap.hpp"

//apenas implementar funcoes heap; heapify, insere etc
//os sucessores estão apenas nas posições (2*i + 1 e 2*i + 2)
//ancestral está em floor((i-1)/2);

/*Nesta atividade, você deve implementar um programa que
manipula uma estrutura de Min Heap. O programa deve:
1. Lê da entrada padrão:
❑ Um número inteiro n, indicando o tamanho do Min Heap.
❑ n inteiros, representando os elementos a serem inseridos
no Min Heap.
2. Inserir os n elementos na estrutura de dados na ordem de
leitura.
3. Remover todos os elementos do Min Heap e imprimi-los na
ordem de remoção, separados por um espaço em branco.
Finalize a saída com uma quebra de linha.*/

static void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int Heap::GetAncestral(int posicao) {
    return (posicao-1)/2;
}

int Heap::GetSucessorEsq(int posicao) {
    return 2*posicao + 1;
}

int Heap::GetSucessorDir(int posicao) {
    return 2*posicao + 2;
}

void Heap::HeapifyPorBaixo(int posicao) {
    if (posicao >= tamanho)
        return;
        
    int dir = GetSucessorDir(posicao);
    int esq = GetSucessorEsq(posicao);
    int menor = posicao;
    if (esq < tamanho && data[esq] < data[menor])
        menor = esq;
    if (dir < tamanho && data[dir] < data[menor])
        menor = dir;
    //int x = min(data[GetSucessorEsq(posicao)], data[GetSucessorDir(posicao)]);
    if (menor != posicao) {
        swap(data[posicao], data[menor]);
        HeapifyPorBaixo(menor);
    }
}

void Heap::HeapifyPorCima(int posicao) {
    if (posicao <= 0)
        return;
    
    int p = GetAncestral(posicao);
    while(data[posicao] < data[p]) {
        swap(data[posicao], data[p]);
        HeapifyPorCima(p);
    }
}

Heap::Heap(int maxsize) {
    data = new int[maxsize];
    tamanho = 0;
}

Heap::~Heap() {
    delete[] data;
}

void Heap::Inserir(int x) {
    data[tamanho] = x;  //minheap
    tamanho++;
    HeapifyPorCima(tamanho-1);
}

int Heap::Remover() {
    if (Vazio())
        return -1;
    
    int raiz = data[0];//remoção propriamente dita, agora é fazer heapify
    swap(data[0],data[tamanho - 1]); 
    tamanho--;
    HeapifyPorBaixo(0);
    
    return raiz;
}

bool Heap::Vazio() {
    if (!tamanho)
        return true;
    return false;
}