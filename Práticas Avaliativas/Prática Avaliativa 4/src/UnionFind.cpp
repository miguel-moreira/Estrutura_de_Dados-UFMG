#include "UnionFind.hpp"

UnionFind::UnionFind(int quantidade_subconjuntos) {
    tamanho = quantidade_subconjuntos;
    subconjuntos = new Subconjunto[tamanho];
    for (int i = 0; i < tamanho; ++i) {
        Make(i);
    }
}

UnionFind::~UnionFind() {
    delete[] subconjuntos;
}

void UnionFind::Make(int x) {
    subconjuntos[x].representante = x;
    subconjuntos[x].rank = 0;
}

int UnionFind::Find(int x) {
    if (subconjuntos[x].representante != x) {
        subconjuntos[x].representante = Find(subconjuntos[x].representante);
    }
    return subconjuntos[x].representante;
}

void UnionFind::Union(int x, int y){
    int raizx = Find(x);
    int raizy = Find(y);

    if (raizx == raizy) return;

    if (subconjuntos[raizx].rank < subconjuntos[raizy].rank) {
        subconjuntos[raizx].representante = raizy;
    } else if (subconjuntos[raizx].rank > subconjuntos[raizy].rank) {
        subconjuntos[raizy].representante = raizx;
    } else {
        subconjuntos[raizy].representante = raizx;
        subconjuntos[raizx].rank++;
    }
}