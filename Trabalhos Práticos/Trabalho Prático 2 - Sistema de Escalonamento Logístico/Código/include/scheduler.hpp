#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include "heap.hpp"
#include "eventandparameters.hpp"

// Classe responsável por definir o escalonador de eventos.

class scheduler {
    private:
        // Atributo único, um heap de eventos.
        heap<event> eventScheduler;    
    
    public: 
        // Método de inserção de novos eventos no heap.
        void insertEvent(const event& _event);
        
        // Método de remoção de eventos do heap, irá tirar o menor (raiz) por ser um minheap.
        event removeEvent();
        
        // Método que testa se o 'eventScheduler' possui eventos armazenados ou não.
        bool empty() const;
};

#endif