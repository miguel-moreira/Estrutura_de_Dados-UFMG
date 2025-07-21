#ifndef AVL_TREE
#define AVL_TREE

#include <stdio.h> // fprintf.
#include "algorithms.hpp" // max.

// Arquivo para definição e implementação de uma árvore binária genérica.

// Struct genérica para 'node', para que a árvore opere com qualquer tipo de dados.
template<typename T>
struct node {
    // Atributos genéricos.
    T data;
    node<T>* left;
    node<T>* right;
    int height;

    // Construtores padrão e parametrizado.
    node() : data(), left(nullptr), right(nullptr), height(1) {}
    node(const T& _data) : data(_data), left(nullptr), right(nullptr), height(1) {}
};

// Classe responsável pela árvore binária propriamente dita.
template<typename T>
class tree {
    private:
        // Atributo raiz da árvore, necessário para inicializar os outros.
        node<T>* root;

        // Método que será chamado pelo destrutor para desalocar a memória.
        void destroyRecursive(node<T>* _node);

        // Método que será chamado pelo 'insert' para inserir um novo elemento.
        node<T>* insertRecursive(node<T>* _node, const T& _data);

        // Método para retornar a altura de um 'node' específico.
        int height(node<T>* _node);

        // Método para retornar o balance de um 'node', para checar se é necessário rotacionar ou não.
        int getBalance(node<T>* _node);

        // Método para rotacionar à direita.
        node<T>* rotateRight(node<T>* _node);

        // Método para rotacionar à esquerda.
        node<T>* rotateLeft(node<T>* _node);

    public: 
        // Construtor e destrutor da árvore, necessários para manipular a memória e os apontadores corretamente.
        tree();
        ~tree();
        
        // Método para buscar um node específico na árvore.
        node<T>* find(const T& _key);

        // Método para inserir um node na árvore.
        void insert(const T& _data);

};

// Método que realmente destrói a árvore, desaloca as subárvores de cada node e o node.
template<typename T>
void tree<T>::destroyRecursive(node<T>* _node) {
    try {
        if (_node != NULL) {
            destroyRecursive(_node->left);
            destroyRecursive(_node->right);
            delete _node;
        }
    } catch (...) {
        fprintf(stderr, "Error while destroying AVL Tree.\n");
    }
}

// Método responsável pela inserção, vai percorrendo a árvore, atualizando as alturas e
// realizando as rotações necessárias para manter o balanceamento.
template<typename T>
node<T>* tree<T>::insertRecursive(node<T>* _node, const T& _data) {
    try {
        if (!_node) {
            return new node<T>(_data);
        }
    
        if (_data < _node->data) {
            _node->left = insertRecursive(_node->left, _data);
        } else if (_data > _node->data) {
            _node->right = insertRecursive(_node->right, _data);
        } else {
            return _node;
        }
    
        _node->height = 1 + max(height(_node->left), height(_node->right));
        int balance = getBalance(_node);
    
        // Caso 1 - Left Left
        if ((balance > 1) and (_data < _node->left->data)) {
            return rotateRight(_node);
        }
    
        // Caso 2 - Right Right
        if ((balance < -1) and (_data > _node->right->data)) {
            return rotateLeft(_node);
        }
    
        // Caso 3 - Left Right
        if ((balance > 1) and (_data > _node->left->data)) {
            _node->left = rotateLeft(_node->left);
            return rotateRight(_node);
        }
    
        // Caso 4 - Right Left
        if ((balance < -1) and (_data < _node->right->data)) {
            _node->right = rotateRight(_node->right);
            return rotateLeft(_node);
        }
    
        return _node;
    } catch (...) {
        fprintf(stderr, "Error while inserting new element in the tree.\n");
    }
    
    return root;
}

// Método para o retorno da altura de um node.
template<typename T>
int tree<T>::height(node<T>* _node) {
    return (_node == nullptr) ? 0 : _node->height;
}

// Método para o cálculo e retorno do balanceamento de um node.
template<typename T>
int tree<T>::getBalance(node<T>* _node) {
    return height(_node->left) - height(_node->right);
}

// Método para realizar rotação à direita.
template<typename T>
node<T>* tree<T>::rotateRight(node<T>* _node) {
    try {
        node<T>* leftNode = _node->left;
        node<T>* auxNode = leftNode->right;
    
        leftNode->right = _node;
        _node->left = auxNode;
    
        _node->height = 1 + max(height(_node->left), height(_node->right));
        leftNode->height = 1 + max(height(leftNode->left), height(leftNode->right));
    
        return leftNode;
    } catch (...) {
        fprintf(stderr, "Error in the right rotation.\n");
    }
}

// Método para realizar a rotação à esquerda;
template<typename T>
node<T>* tree<T>::rotateLeft(node<T>* _node) {
    try {
        node<T>* rightNode = _node->right;
        node<T>* auxNode = rightNode->left;
    
        rightNode->left = _node;
        _node->right = auxNode;
    
        _node->height = 1 + max(height(_node->left), height(_node->right));
        rightNode->height = 1 + max(height(rightNode->left), height(rightNode->right));
    
        return rightNode;
    } catch (...) {
        fprintf(stderr, "Error in the left rotation.\n");
    }
}

// Construtor da árvore, delega ao construtor do node.
template<typename T>
tree<T>::tree() : root(nullptr) {}

// Destrutor da árvore, responsável por liberar toda a memória alocada por ela dinamicamente.
template<typename T>
tree<T>::~tree() {
    destroyRecursive(root);
}

// Método para encontrar um node específico da árvore a partir da sua chave. Irá apenas percorrer a árvore checando se o node com a '_key' existe ou não. Se existir, retorna o node, se não, retorna null.
template<typename T>
node<T>* tree<T>::find(const T& _key) {
    try {
        node<T>* current = root;
        while (current != nullptr) {
            if (current->data == _key) {
                return current;
            }
            if (current->data > _key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        
        return nullptr;
    } catch (...) {
        fprintf(stderr, "Error while trying to find _key in tree.\n");
    }
}

// Método da inserção de node. Irá checar se árvore está vazia, caso esteja, cria uma nova raiz e insere, caso contrário, irá percorrer a árvore até achar a folha correta, no fim, verificamos se deve ir à esquerda ou direita desta folha e é inserido.
template<typename T>
void tree<T>::insert(const T& _data) {
    root = insertRecursive(root, _data);
}

#endif