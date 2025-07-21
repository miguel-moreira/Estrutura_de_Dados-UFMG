#ifndef LISTADEADJACENCIA_HPP
#define LISTADEADJACENCIA_HPP

#include "listaencadeada.hpp"

struct NodeVertice {
    int id;
    NodeVertice* next;
    ListaEncadeada* lista;

    NodeVertice(int _id) : id(_id), next(nullptr), lista(new ListaEncadeada()) {}
};

class ListaAdjacencia {
    private:
        NodeVertice* head;
    public:
        ListaAdjacencia() : head(nullptr) {}
        ~ListaAdjacencia();

        NodeVertice* getHead();
        void insereAresta(int v, int w);
        void insereVertice(int v);
        int tamanhoLista();
};

#endif
