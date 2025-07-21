#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"
#include <cstdlib> //exit
#include <stdio.h> //fprintf

//Classe para implementação da pilha dinâmica e flexível, usando vector como estrutura para armazenar os dados.

template<typename T>
class stack {
    private:
        // Atributo único de vector, que facilita muito a implementação dos métodos a seguir. 
        vector<T> data;

    public:
        // Construtor e destrutor padrões, irão delegar ao vector.
        // Construtor de cópia garantindo a regra dos três.
        stack();
        stack(const stack<T>& other);
        ~stack();

        // Método para inserção de elementos na pilha.
        void push(const T& element);
        
        // Método para remoção de elementos na pilha.
        void pop();
        
        // Método para pegar o último elemento inserido na pilha.
        T& top();
        
        // Método padrão para checar se a pilha está vazia.
        bool empty() const;
        
        // Método para retornar o tamanho atual da pilha.
        int size() const;

        // Sobrecarga do operador '=', permitindo cópias entre pilhas.
        stack<T>& operator=(const stack<T>& other);
};

// IMPLEMENTAÇÃO DOS MÉTODOS

// Construtor delega para o construtor padrão do vector, iniciando data com 0 elementos.
template<typename T>
stack<T>::stack() {}

// Construtor delega para a sobrecarga do operador '=' implementado no vector.
template<typename T>
stack<T>::stack(const stack<T>& other) {
    this->data = other.data;
}

// Destrutor delega para o destrutor do vector.
template<typename T>
stack<T>::~stack() {}

// Método de inserção na pilha, apenas insere normalmente no vector utilizando o método 'push_back()'.
template<typename T>
void stack<T>::push(const T& element) {
    data.push_back(element);
}

// Método de remoção de elementos da pilha, irá remover o último elemento mantendo a lógica LIFO,
// Então é necessário apenas chamar o 'pop_back()' do vector.
template<typename T>
void stack<T>::pop() {
    if (!(data.size())) {
        fprintf(stderr,"Stack is already empty.\n");
    } else {
        data.pop_back();
    }
}

// Método que retorna o elemento no topo da pilha, logo o último elemento do vector, LIFO, caso  a pilha esteja vazia,
// Finaliza a execução do programa, porque levaria a um acesso de memória inexistente.
template<typename T>
T& stack<T>::top() {
    if (!data.size()) {
        fprintf(stderr, "Pilha está vazia.\n");
        exit(EXIT_FAILURE);
    }
    return data[data.size() - 1];
}

// Método para checar se a pilha está vazia ou não, então apenas checa se o vector tem elementos armazenados ou não,
// Utilizando 'size()' implementado no vector.
template<typename T>
bool stack<T>::empty() const {
    if (!(data.size())) {
        return true;
    } 
        
    return false;
}

// Retorna o tamanho da pilha, ou seja, a quantidade de elementos armazenados no vector.
template<typename T>
int stack<T>::size() const {
    return data.size();
}

// Sobrecarga do operador '=', permitindo que uma pilha receba os elementos de outra, delega para a sobrecarga
// Do operador '=' do vector.
template<typename T>
stack<T>& stack<T>::operator=(const stack<T>& other) {
    if (this != &other) { 
        this->data = other.data;
    }
    
    return *this;
}

#endif