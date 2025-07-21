#include "heap.hpp"
#include <iostream>

int main(){
    int n = 0, element = 0;
    std::cin >> n;
    
    Heap MinHeap(n);
    
    for (int i = 0; i < n; i++) {
        std::cin >> element;
        MinHeap.Inserir(element);
    }
    
    int removido;
    for (int i = 0; i < n; i++) {
        removido = MinHeap.Remover();
        std::cout << removido << " ";
    }
    
    std::cout << std::endl;
    
    return 0;
}