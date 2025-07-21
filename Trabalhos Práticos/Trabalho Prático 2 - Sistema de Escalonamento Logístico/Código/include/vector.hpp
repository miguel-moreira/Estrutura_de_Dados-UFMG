#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stdio.h> //fprintf

// Classe para implementação do vetor dinâmico e flexível a qualquer tipo de dados usado.
template<typename T>
class vector {
private:
    // Atributos do vector, dado, capacidade, tamanho.
    T* data;
    int _capacity;
    int _size;

    // Método necessário para inserir novos elementos caso o espaço seja insuficiente.
    void expand();

public:
    // Sobrecarregando para caso o usuário já tenha tamanho pré-definido, caso contrário a inserção pode ser feita sob mediada. 
    // Destrutor e construtor de cópia também implementados, garantindo a regra dos três.
    vector();
    vector(int capacity);
    vector(int capacity, T element);
    ~vector();
    vector(const vector& other);

    // Método para inserção de novos elementos no fim do vetor.
    void push_back(const T& element);

    // Método para remoção de elementos ao fim do vetor.
    void pop_back();

    // Métodos elementares para uso do usuário e para inserção.
    int size() const;

    // Método para 'limpar' o vector, perdendo os elementos já alocados.
    void clear();

    // Sobrecarga do operador '[]', para que seja possível acessar elementos pelas respectivas posições.
    // Também para que os elementos em certas posições possam ser alterados.
    T& operator[](int index);
    const T& operator[](int index) const;

    // Sobrecarga do operador '=', para que todos os valores de um vector possam ser atribuídos a outro vector.
    vector<T>& operator=(const vector<T>& other);
};

//IMPLEMENTAÇÃO DOS MÉTODOS

// Construtor inicia o vector com 0 elementos.
template<typename T>
vector<T>::vector() : data(nullptr), _capacity(1), _size(0) {
    try {
        data = new T[_capacity];
    } catch (...) {
        fprintf(stderr, "Erro ao alocar memória no construtor padrão.\n");
    }
}

// Construtor que usa tamanho sob-medida e aloca dependendo da exigência do usuário.
template<typename T>
vector<T>::vector(int __capacity) : data(nullptr), _capacity(__capacity), _size(0) {
    try {
        data = new T[_capacity];
    } catch (...) {
        fprintf(stderr, "Erro ao alocar memória no construtor padrão.\n");
    }
}

template<typename T>
vector<T>::vector(int __capacity, T element) : data(nullptr), _capacity(__capacity), _size(__capacity) {
    try {
        data = new T[_capacity];
        for (int i = 0; i < __capacity; i++) {
            data[i] = element;
        }
    } catch (...) {
        fprintf(stderr, "Erro ao alocar memória no construtor padrão.\n");
    }
}

// Destrutor, desalocando a memória dedicada ao vector.
template<typename T>
vector<T>::~vector() {
    delete[] data;
}

// Construtor de cópia, que aloca um espaço com a mesma capacidade que o original e copia os elementos um a um, garantindo igualdade.
template<typename T>
vector<T>::vector(const vector<T>& other) : data(nullptr), _capacity(other._capacity), _size(other._size) {
    try {
        data = new T[_capacity];
        for (int i = 0; i < _size; ++i) {
            data[i] = other.data[i];
        }
    } catch (...) {
        fprintf(stderr, "Erro ao copiar vetor no construtor de cópia.\n");
    }
}

// Método que torna possível a alocação dinâmica. Aumenta em 2 vezes o tamanho do vector e aloca a memória necesária para o respectivo processo.
// Depois, passa os dados do vector antigo (menor) para o novo (maior). Por fim, desaloca o vector antigo e atualiza o vector atual com o valor do novo.
template<typename T>
void vector<T>::expand() {
    try {
        _capacity *= 2;
        T* newData = new T[_capacity];
        for (int i = 0; i < _size; ++i)
            newData[i] = data[i];

        delete[] data;
        data = newData;
    } catch (...) {
        fprintf(stderr, "Erro ao expandir vetor.\n");
    }

}

// Método responsável por inserir os novos elementos no vector. Verifica se o tamanho do vector está dentro da capacidade (memória alocada).
// Caso não esteja, chama a função expandir() e, com o novo espaço alocado, o elemento passado por referência é inserido na última posição e o tamanho aumenta em 1.
template<typename T>
void vector<T>::push_back(const T& element) {
    try {
        if (_size == _capacity)
            expand();

        data[_size++] = element;
    } catch (...) {
        fprintf(stderr, "Erro ao inserir elemento no vetor.\n");
    }
}

template<typename T>
void vector<T>::pop_back() {
    try {
        if (_size > 0) {
            _size--;
        } else {
            fprintf(stderr, "Vetor já não possui nenhum elemento.\n");
        }
    } catch (...) {
        fprintf(stderr, "Erro ao remover elemento do vetor.\n");
    }
}

// Método elementar para retornar o tamanho (quantidade de elementos) do vector.
template<typename T>
int vector<T>::size() const {
    return _size;
}

// Método para limpar o vector. Torna o tamanho 0, ou seja, os elementos anteriores são perdidos mas a capacidade é mantida.
// Então o vector pode ter (capacidade) novos elementos inseridos.
template<typename T>
void vector<T>::clear() {
    _size = 0;
}

// Sobrecaraga do operator[] para poder acessar elementos do vector diretamente a partir de um index recebido, e.g. vector[1] = 4. 
// É a versão não constante, então permite a leitura e alteração do elemento em questão.
template<typename T>
T& vector<T>::operator[](int index) {
    return data[index];
}

// Similiar à sobrecarga definida anteriormente, mas a versão constante, que só permite leitura e não permite alteração do elemento.
template<typename T>
const T& vector<T>::operator[](int index) const {
    return data[index];
}

// Sobrecarga do operador '=', que permite a atribuição dos valores de um vetor a outro integralmente.
// Verifica caso já sejam iguais, porque o processo é custoso. O vetor que está recebendo a atribuição têm sua memória desalocada.
// Depois, as informações são copiadas de um vector ao outro e a nova memória é alocada.
// Por fim, o vetor que recebeu outro como atribuição é retornado.
template<typename T>
vector<T>& vector<T>::operator=(const vector<T>& other) {
    if (this->data == other.data) {
        return *this;
    }

    try {
        delete[] data;
        this->_size = other._size;
        this->_capacity = other._capacity;
        data = new T[_capacity];

        for (int i = 0; i < this->_size; ++i) {
            data[i] = other.data[i];
        }
    } catch (...) {
        fprintf(stderr, "Erro ao atribuir vetor.\n");
    }

    return *this;
}

#endif