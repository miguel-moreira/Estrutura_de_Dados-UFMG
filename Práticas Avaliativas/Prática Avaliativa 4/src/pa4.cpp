#include "UnionFind.hpp"
#include "sorts.hpp"
#include "vector.hpp"
#include <iostream>

int main() {
    int n, m;
    std::cin >> n >> m;

    vector<Aresta> arestas(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> arestas[i].u >> arestas[i].v >> arestas[i].custo;
    }

    insertionSort(arestas, 0, arestas.tamanho()-1);

    UnionFind uf(n);
    int custo_total = 0;
    int arestas_usadas = 0;

    for (int i = 0; i < m; ++i) {
        int u = arestas[i].u;
        int v = arestas[i].v;

        if (uf.Find(u) != uf.Find(v)) {
            uf.Union(u, v);
            custo_total += arestas[i].custo;
            arestas_usadas++;
        }

        if (arestas_usadas == n - 1) break;
    }

    std::cout << custo_total << std::endl;

    return 0;
}