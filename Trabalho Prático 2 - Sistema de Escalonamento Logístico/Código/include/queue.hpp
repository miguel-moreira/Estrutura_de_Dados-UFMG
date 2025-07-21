#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "vector.hpp"

//Classe para implementação da fila dinâmica e flexível, utilizando vector como estrutura para armazenar os dados.

template<typename T>
class queue {
private:
    // vector para armazenar os elementos e start será o index para descobrir onde a pilha começa no vector.  
    vector<T> data;
    int start;

public:
    // Construtor e destrutor padrões    
    queue();
    ~queue();

    // Método para inserir elementos na fila.    
    void push(const T& element);
    
    // Método para remover elementos da fila.
    void pop();
    
    // Método que retorna o primeiro elemento inserido na fila.
    const T& front() const;
    
    // Método para checar se há elementos na fia.
    bool empty() const;
};

// Construtor delega a construção de 'data' para o construtor padrão do vector.
template<typename T>
queue<T>::queue() : start(0) {}

// Destrutor padrão, delega parte ao destrutor do vector e 'start' é apenas uma variável simples.
template<typename T>
queue<T>::~queue() {}

// Método para inserir na fila, apenas insere o elemento no vector utilizando o método 'push_back()' do vector.
template<typename T>
void queue<T>::push(const T& element) {
    data.push_back(element);
}

// Método para remover elemento da pilha, apenas vai andar a posição do 'start', perdendo o elemento mais a esquerda, FIFO.
template<typename T>
void queue<T>::pop() {
    if (empty()) {
        fprintf(stderr, "Queue is empty.\n");
        return;
    }
    start++;
}

// Método que retorna a frente da fila, apenas acessa o índice 'start' em 'data'.
template<typename T>
const T& queue<T>::front() const {
    if (empty()) {
        fprintf(stderr, "Queue is empty.\n");
    }
    return data[start];
}

// Método para checar se a fila tem elementos ou não, checando se o 'start' é igual ao tamanho de 'data',
// O que significa que não há elementos na fila.
template<typename T>
bool queue<T>::empty() const {
    return start >= data.size();
}

#endif