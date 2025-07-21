#include "graph.hpp"

Grafo::Grafo() {}//ambos já estão implementados na listaAdj
             //grafo é apenas uma instancia de listaAdj^
Grafo::~Grafo() {}

void Grafo::InsereVertice(int v) {
    vertices.insereVertice(v);
}

void Grafo::InsereAresta(int v, int w) {
    vertices.insereAresta(v,w);
}

int Grafo::QuantidadeVertices() {
    return vertices.tamanhoLista();
}

int Grafo::QuantidadeArestas() {
    int count = 0;
    NodeVertice* current = vertices.getHead();

    while (current) {
        if (current->lista)
            count += current->lista->tamanhoLista();
        else
            count += 0;
        current = current->next;
    }

    return count / 2;
}

int Grafo::GrauMinimo() {
    int grau = 0;
    NodeVertice* current = vertices.getHead();

    if (!(current))
        return 0;

    int graumin = current->lista->tamanhoLista();
    current = current->next;

    while (current) {
        grau = current->lista->tamanhoLista();
        if (grau < graumin)
            graumin = grau;
        current = current->next;
    }

    return graumin;
}

int Grafo::GrauMaximo() {
    int grau = 0;                                           //solução=funcao getter para o head;
    NodeVertice* current = vertices.getHead();              //head privado + vertices estatico^
            //vertices->head ou head ou vertices.head nao funcionam^
    if (!(current))
        return 0;

    int graumax = current->lista->tamanhoLista();
    current = current->next;

    while (current) {
        grau = current->lista->tamanhoLista();
        if (grau > graumax)
            graumax = grau;
        current = current->next;
    }

    return graumax;
}

void Grafo::ImprimeVizinhos(int v) {
    NodeVertice* current = vertices.getHead();

    if (!(current))
        return;

    while (current) {
        if (current->id == v)
            current->lista->imprimirLista();
        current = current->next;
    }
}
