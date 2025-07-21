#include "graph.hpp"
#include <cstring>

void LerGrafo(Grafo &g) {
    int numvertices = 0;
    std::cin >> numvertices;

    for (int i = 0; i < numvertices; i++) {
        g.InsereVertice(i);
    }

    int m = 0, aresta = 0;
    for (int i = 0; i < numvertices; i++) {
        std::cin >> m;
        for (int j = 0; j < m; j++) {
            std::cin >> aresta;
            g.InsereAresta(i,aresta);
        }
    }
}

void DadosBasicos(Grafo &g) {
    std::cout << g.QuantidadeVertices() << std::endl;
    std::cout << g.QuantidadeArestas() << std::endl;
    std::cout << g.GrauMinimo() << std::endl;
    std::cout << g.GrauMaximo() << std::endl;
}

void Vizinhancas(Grafo &g) {
    for (int i = 0; i < g.QuantidadeVertices(); i++) {
        g.ImprimeVizinhos(i);
        std::cout << std::endl;
    }
}

int IsComplete(Grafo &g) {
    bool stat1 = g.GrauMaximo() == g.GrauMinimo();//grau max = grau min && num arestas = nv(nv-1)/2
    bool stat2 = g.QuantidadeArestas() == g.QuantidadeVertices() * (g.QuantidadeVertices() - 1) / 2;
    if (stat1 and stat2)
        return 1;
    
    return 0;
}

int main(int argc, char* argv[]) {
    
    Grafo g;
    
    int d = 0, n = 0, k = 0;

    if (strcmp(argv[1], "-d") == 0) {
        d = 1;
    } else if (strcmp(argv[1], "-n") == 0) {
        n = 1;
    } else if (strcmp(argv[1], "-k") == 0) {
        k = 1;
    }
    
    LerGrafo(g);

    if (d)
        DadosBasicos(g);
    else if (n)
        Vizinhancas(g);
    else if (k) {
        int x = IsComplete(g);
        std::cout << x << std::endl;   
    }

    return 0;
}
