#include "listaencadeada.hpp"

ListaEncadeada::~ListaEncadeada() {
    Node* current = head;
    while (current) {
        Node* temp = current;//delete de cima p/ baixo
        current = current->next;
        delete temp;
    }
}

Node* ListaEncadeada::acharNode(int v) {
    Node* current = head;
    while (current) {
        if (current->id == v)
            return current;
        else
            current = current->next;
    }
    return nullptr;
}

void ListaEncadeada::insereNode(int v) {
    Node* newNode = new Node(v);//insere no fim da lista

    if (!head) {
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next != nullptr) 
        current = current->next;
    current->next = newNode;
}

int ListaEncadeada::tamanhoLista() {
    int count = 0;

    Node* current = head;
    while (current) {
        current = current->next;
        count++;
    }

    return count;
}

void ListaEncadeada::imprimirLista() {
    Node* current = head;
    while (current) {
        std::cout << current->id;
        if (current->next) {
            std::cout << " ";
        }
        current = current->next;
    }
}
