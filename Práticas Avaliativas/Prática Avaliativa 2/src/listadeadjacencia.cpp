#include "listadeadjacencia.hpp"

ListaAdjacencia::~ListaAdjacencia() {
    NodeVertice* current = head;
    while (current) {
        NodeVertice* temp = current;
        current = current->next;
        delete temp->lista;
        delete temp;
    }
}

NodeVertice* ListaAdjacencia::getHead() {
    return head;
}

void ListaAdjacencia::insereAresta(int v, int w) {
    NodeVertice* current = head;
    while (current) {
        if (current->id == v) {
            current->lista->insereNode(w);
            return;
        }
        current = current->next;
    }
}

void ListaAdjacencia::insereVertice(int v) {
    NodeVertice* newNodeV = new NodeVertice(v);
    NodeVertice* current = head;

    if (!head) {
        head = newNodeV;
        return;
    }

    while (current->next)
        current = current->next;

    current->next = newNodeV;
}

int ListaAdjacencia::tamanhoLista() {
    int count = 0;
    NodeVertice* current = head;

    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

