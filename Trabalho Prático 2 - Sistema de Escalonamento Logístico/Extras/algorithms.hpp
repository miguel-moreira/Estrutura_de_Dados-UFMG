#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "queue.hpp" //vector
#include "stack.hpp" //vector

// Declaração de um valor grande o suficiente para que seja considerado infinito.
const int INF = 0x3f3f3f3f;

// Arquivo dedicado a algoritmos genéricos utilizados em outras seções do código.

// Estrutura para representar uma aresta ponderada na lista de adjacência.
template<typename T, typename W>
struct edge {
    T neighbor;
    W weight;
};

// Estrutura para armazenar os nós na minheap, contendo o nó e sua distância da origem.
template<typename T, typename W>
struct nodeDistance {
    T node;
    W distance;

    // Sobrecarga do operador '<' para que o minheap os ordene de maneira correta.
    bool operator<(const nodeDistance& other) const {
        return distance < other.distance;
    }
};

// Função para trocar o valor entre duas variáveis genéricas utilizando uma terceira temporária.
template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// Implementação de um algoritmo de Dijkstra, retornando uma stack como rota.
// O funcionamento é baseado na escolha ótima de arestas (menor peso) até o destino, encontrando o menor e mais barato caminho.
// Utiliza o minheap para eficiência de escolha e structs personalizadas para representar arestas e nós.
// O grafo deve ser uma lista de adjacência do tipo 'vector<vector<edge<T, W>>>'.
// O retorno é uma pilha com a rota em ordem inversa. Se não houver caminho, a pilha estará vazia.
template<typename T, typename W = int>
stack<T> dijkstra(vector<vector<edge<T, W>>>& graph, T originNode, T destinationNode) {
    int n = graph.size();
    if (n == 0) return stack<T>();

    vector<W> distances(n, INF);
    vector<T> parent(n, -1);
    minheap<nodeDistance<T, W>> pq;

    distances[originNode] = 0;
    pq.push({originNode, 0});

    while (!pq.empty()) {
        nodeDistance<T, W> current = pq.top();
        pq.pop();

        T currentNode = current.node;
        W currentDist = current.distance;

        if (currentDist > distances[currentNode]) {
            continue;
        }

        if (currentNode == destinationNode) {
            break;
        }

        for (int i = 0; i < graph[currentNode].size(); ++i) {
            edge<T, W> edge = graph[currentNode][i];
            T neighbor = edge.neighbor;
            W weight = edge.weight;

            if (distances[currentNode] + weight < distances[neighbor]) {
                distances[neighbor] = distances[currentNode] + weight;
                parent[neighbor] = currentNode;
                pq.push({neighbor, distances[neighbor]});
            }
        }
    }

    stack<T> route;
    if (distances[destinationNode] == INF) {
        return route;     
    }

    T current = destinationNode;
    while (current != -1) {
        route.push(current);
        current = parent[current];
    }
    
    return route;
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
