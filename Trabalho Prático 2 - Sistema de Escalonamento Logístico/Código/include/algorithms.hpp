#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "queue.hpp" //vector
#include "stack.hpp" //vector

// Arquivo dedicado a algoritmos genéricos utilizados em outras seções do código.

// Função para trocar o valor entre duas variáveis genéricas utilizando uma terceira temporária.
template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// Implementação de uma BFS genérica, que terá como retorno uma 'stack' com a rota.
// O funcionamento dela é baseado na busca em largura, em que o algoritmo explora o grafo por níveis a partir de um nó de origem. 
// Isso garante que o caminho encontrado até o nó de destino seja o mais curto em número de arestas.
// O grafo deve ser uma lista de adjacência (vector<vector<T>>), onde graph[i] contém os vizinhos do nó i.
// O retorno é uma pilha com a rota em ordem inversa (origem no topo). Se não houver caminho, a pilha retornada estará vazia.
template<typename T>
stack<T> BFS(vector<vector<T>>& graph, T originNode, T destinationNode) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<T> parent(n, -1);

    queue<T> q;
    q.push(originNode);
    visited[originNode] = true;

    while (!q.empty()) {
        T current = q.front();
        q.pop();

        if (current == destinationNode) {
            break;
        }

        for (int i = 0; i < graph[current].size(); i++) {
            T neighbor = graph[current][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }

    stack<T> route;
    if (!visited[destinationNode]) {
        return route;
    }

    T current = destinationNode;
    while (current != -1) {
        route.push(current);
        current = parent[current];
    }
    
    return route;
}

// Função genérica simples utilizada pelo heap para achar qual dos três índices fornecidos armazena o menor elemento no vetor.
template<typename T>
int smallestElement(vector<T>& data, int& a, int& b, int& c) {
    T smallest = data[a];

    if (data[b] < smallest) {
        return b;
    }

    if (data[c] < smallest) {
        return c;
    }

    return a;
}

#endif