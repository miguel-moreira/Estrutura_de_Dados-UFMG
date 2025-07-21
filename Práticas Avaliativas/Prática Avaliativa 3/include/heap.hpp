#ifndef HEAP_HPP
#define HEAP_HPP

class Heap{
    private:
        int GetAncestral(int posicao);
        int GetSucessorEsq(int posicao);
        int GetSucessorDir(int posicao);
        int tamanho;
        int* data;
        //Funções necessárias para implementar o Heapify recursivo
        void HeapifyPorBaixo(int posicao);
        void HeapifyPorCima(int posicao);    
    public:
        Heap(int maxsize);
        ~Heap();
        void Inserir(int x);
        int Remover();
        //Retorna 1 caso h esteja vazio, 0 caso contrário.
        bool Vazio();
};

#endif