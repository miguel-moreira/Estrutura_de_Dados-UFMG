#ifndef LISTAENCADEADA_HPP
#define LISTAENCADEADA_HPP

#include <iostream>

struct Node {
    int id;
    Node* next;

    Node(int _id) : id(_id), next(nullptr) {}
};

class ListaEncadeada {
    private:
        Node* head;
    public:
        ListaEncadeada() : head(nullptr) {}
        ~ListaEncadeada();

        Node* acharNode(int v);
        void insereNode(int v);
        int tamanhoLista();
        void imprimirLista();
};

#endif
