// Código para implementação dos métodos da classe warehouse, definidos em warehouse.hpp
#include "../include/warehouse.hpp"

// Método para adição de seção, apenas cria uma nova pilha e a insere no vector que armazena todas as outras seções.
void warehouse::addSession() {
    stack<package> s;
    sessions.push_back(s);
}

// Método para armazenar um pacote, este que carrega as informações de onde vem e para onde deve ir.
// O pacote irá apenas ser inserido na pilha da seção correta.
void warehouse::storePackage(package& pac) {
    sessions[pac.getSession()].push(pac);
 }

// Método para remoção de um pacote de uma pilha 'destination'. O pacote do topo da seção será removido, mantendo a lógica LIFO
// E uma referência a ele será retornada.
package& warehouse::removePackageFor(int destination) {
    package& pac = sessions[destination].top();
    sessions[destination].pop();
    return pac;
}

// Método que apenas testa se a pilha da seção 'destination' possui elementos ou não, implementado usando o 'empty()' feito em 'stack.hpp'.
bool warehouse::hasPackageFor(int destination) {
    if (sessions[destination].empty()) {
        return false;
    }
    return true;
}