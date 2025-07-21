// Código para implementação dos métodos definidos em 'scheduler.hpp'.
#include "../include/scheduler.hpp"

// Método da inserção de eventos, recebe uma referência a evento e o insere no minheap, que faz o balanceamento interno necessário.
void scheduler::insertEvent(const event& _event) {
    eventScheduler.push(_event);
}

// Método da remoção de eventos, apenas remove a raiz do minheap, que se ajusta internamente, e retorna esta raiz.
event scheduler::removeEvent() {
    event e = eventScheduler.top();
    eventScheduler.pop();
    return e;
}

// Método responsável por dizer se o minheap está vazio ou não, testando se o vector do minheap tem elementos ou não.
bool scheduler::empty() const {
    return eventScheduler.empty();
}