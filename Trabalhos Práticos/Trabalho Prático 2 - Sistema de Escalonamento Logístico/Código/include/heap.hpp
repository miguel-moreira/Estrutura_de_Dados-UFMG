#ifndef HEAP_HPP
#define HEAP_HPP

#include "algorithms.hpp" // Inclui o vector e funções auxiliares como swap() e smallestElement().

// Classe para implementação de um min-heap dinâmico e flexível, usando vector como estrutura de armazenamento.

template<typename T>
class heap {
    private:
        // Vector que armazena os elementos do heap de forma sequencial, respeitando a propriedade de heap.
        vector<T> data;

        // Método que calcula o índice do ancestral (pai) de um nó dado o índice atual.
        int getAncestor(int index);

        // Método que calcula o índice do sucessor à direita de um nó, baseado na posição no vetor.
        int getSuccessorRight(int index);

        // Método que calcula o índice do sucessor à esquerda de um nó, baseado na posição no vetor.
        int getSuccessorLeft(int index);

        // Método responsável por restabelecer a propriedade de heap de baixo para cima (inserção).
        void heapifyUp(int index);

        // Método responsável por restabelecer a propriedade de heap de cima para baixo (remoção).
        void heapifyDown(int index);
        
    public:
        // Construtor e destrutor padrão, sem necessidade de lógica especial,
        // pois o vector cuidará da alocação e desalocação de memória.
        heap();
        ~heap();

        // Método para inserir um novo elemento no heap, com reorganização (heapify up).
        void push(T element);

        // Método para remover o menor elemento (raiz), com reorganização (heapify down).
        void pop(); // Implementação como min-heap.

        // Método para acessar o menor elemento do heap (elemento da raiz).
        const T& top() const;

        // Método padrão para checar se o heap está vazio.
        bool empty() const;
};

// IMPLEMENTAÇÃO DOS MÉTODOS

// Retorna o índice do ancestral (pai) de um nó no índice dado. Caso o índice seja 0 (raiz), retorna ele mesmo.
template<typename T>
int heap<T>::getAncestor(int index) {
    if (!(index)) {
        return index;
    }
    return (index - 1) / 2;
}

// Retorna o índice do sucessor à direita de um nó. Caso o índice calculado ultrapasse o tamanho atual, retorna o próprio index.
template<typename T>
int heap<T>::getSuccessorRight(int index) {
    if (data.size() < index * 2 + 2) {
        // Não há sucessor à direita.
        return index;
    }
    return index * 2 + 2;
}

// Retorna o índice do sucessor à esquerda de um nó. Caso o índice calculado ultrapasse o tamanho, retorna o próprio index.
template<typename T>
int heap<T>::getSuccessorLeft(int index) {
    if (data.size() < index * 2 + 1) {
        // Não há sucessor à esquerda.
        return index;
    }
    return index * 2 + 1;
}

// Método para reorganizar o heap após uma inserção.
// Compara o elemento inserido com seu ancestral, e faz trocas enquanto necessário para manter a propriedade de min-heap (pai sempre menor que os filhos).
template<typename T>
void heap<T>::heapifyUp(int index) {
    int ancestor = getAncestor(index);
    
    while (data[index] < data[ancestor]) {
        swap(data[index], data[ancestor]);
        index = ancestor;
        ancestor = getAncestor(index);
    }
}

// Método para reorganizar o heap após uma remoção.
// Compara o nó atual com seus filhos e realiza trocas para restabelecer a propriedade de min-heap (menor elemento na raiz).
template<typename T>
void heap<T>::heapifyDown(int index) {
    int successorRight = getSuccessorRight(index);
    int successorLeft = getSuccessorLeft(index);

    // Função auxiliar smallestElement() encontra o menor entre o nó atual e seus filhos.
    int smallest = smallestElement(data, successorRight, successorLeft, index);

    while (data[smallest] < data[index]) {
        swap(data[index], data[smallest]);
        index = smallest;
        successorRight = getSuccessorRight(index);
        successorLeft = getSuccessorLeft(index);
        smallest = smallestElement(data, successorRight, successorLeft, index);
    }
}

// Construtor padrão: não faz nenhuma inicialização especial.
template<typename T>
heap<T>::heap() {}

// Destrutor padrão: também não necessita lógica especial.
template<typename T>
heap<T>::~heap() {}

// Insere um elemento no heap.
// Adiciona o elemento no final do vetor e sobe o elemento para a posição correta via heapifyUp.
template<typename T>
void heap<T>::push(T element) {
    data.push_back(element);
    heapifyUp(data.size() - 1);
}

// Remove o elemento da raiz (menor elemento).
// Substitui a raiz pelo último elemento e depois aplica heapifyDown para reorganizar.
template<typename T>
void heap<T>::pop() {
    data[0] = data[data.size() - 1];
    data.pop_back();
    heapifyDown(0);
}

// Retorna o elemento da raiz (menor elemento do heap).
template<typename T>
const T& heap<T>::top() const {
    return data[0];
}

// Retorna verdadeiro se o heap estiver vazio (sem elementos).
template<typename T>
bool heap<T>::empty() const {
    if (!(data.size())) {
        return true;
    }
    return false;
}

#endif