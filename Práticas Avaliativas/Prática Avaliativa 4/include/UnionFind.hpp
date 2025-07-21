#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP

struct Aresta{
    int u;
    int v;
    int custo;

    bool operator<(const Aresta& other) const {
        return custo < other.custo;
    }
    bool operator>(const Aresta& other) const {
        return custo > other.custo;
    }
    bool operator==(const Aresta& other) const {
        return custo == other.custo;
    }
    bool operator<=(const Aresta& other) const {
        return custo <= other.custo;
    }
};

typedef struct s_subset{
    int representante;
    int rank;
} Subconjunto;

class UnionFind{
   private:
        int tamanho;
        Subconjunto* subconjuntos;
 
    public:
        UnionFind(int quantidade_subconjuntos);
        ~UnionFind();
        
        void Make(int x);
        int Find(int x);
        void Union(int x, int y);
};

#endif