// Código para implementar os métodos declarados em 'package.hpp'
#include "../include/package.hpp"

// Construtor padrão, não inicializa rota e inicializa todo o resto com -1.
package::package() {
    this->ID = -1;
    this->origin = -1;
    this->destination = -1;
    this->arrivalTime = -1;
    this->timeStored = -1;
    this->timeTransported = -1;
    this->session = -1;
}

// Construtor parametrizado, é o usado durante a execução do programa, inicializa as variáveis de nome semelhante
// Aos parâmetros.
package::package(int _ID, int _origin, int _destination, int _arrivalTime) {
    this->ID = _ID;
    this->origin = _origin;
    this->destination = _destination;
    this->arrivalTime = _arrivalTime;
    this->timeStored = 0;
    this->timeTransported = 0;
    this->session = -1;
}

// Construtor de cópia, que recebe outro pacote e copia as informações de um para outro. Só é possível graças a
// Sobrecarga do operado '=' na stack.
package::package(const package& other) {
    this->ID = other.ID;
    this->origin = other.origin;
    this->destination = other.destination;
    this->arrivalTime = other.arrivalTime;
    this->timeStored = other.timeStored;
    this->timeTransported = other.timeTransported;
    this->route = other.route;     
    this->session = other.session;
}

// Destrutor padrão, irá delegar uma parte à stack (que delega ao vector) e a outra fará sozinho.
package::~package() {}

// Checa se a rota atual está vazia, caso esteja, finaliza a execução, caso contrário, remove o topo da pilha.
void package::advanceRoute() {
    try {
        if (route.empty()) {
            fprintf(stderr, "Empty.\n");
            return;
        }
        route.pop();
    } catch (...) {
        fprintf(stderr, "Error while trying to advance route.\n");
    }
}

// Testa se é a rota está vazia, não estando, retira o topo, caso a rota tenha ficado vazia, quer dizer que o
// Pacote chegou ao destino, então a seção se torna -1, caso haja mais elementos na pilha, a seção será o segundo elemento
// Retirado, que depois é rearmazenado.
void package::adjustSession() {
    try {
        if (route.empty()) {
            fprintf(stderr, "Impossible to adjust session, empty stack.\n");
            return;
        }
        int top = route.top();
        route.pop();
        if (!route.empty()) {
            this->session = route.top();
            route.push(top);
        } else {
            route.push(top);
            this->session = -1;
        }
    } catch (...) {
        fprintf(stderr, "Error while trying to adjust session.\n");
    }
}

// Método setter usado no cálculo da rota do pacote.
void package::setRoute(stack<int>& _route) {
    this->route = _route;
}

// Método para somar tempo transportado.
void package::addTimeTransported(int time) {
    this->timeTransported += time;
}

// Método para somar tempo armazenado.
void package::addTimeStored(int time) {
    this->timeStored += time;
}

// MÉTODOS GETTERS

// Para ID.
int package::getID() {
    return this->ID;
}

// Para tempo de chegada.
int package::getArrivalTime() {
    return this->arrivalTime;
}

// Para tempo armazenado.
int package::getTimeStored() {
    return this->timeStored;
}

// Para tempo transportado.
int package::getTimeTransported() {
    return this->timeTransported;
}

// Para armazém de origem.
int package::getOrigin() {
    return this->origin;
}

// Para armazém de destino.
int package::getDestination() {
    return this->destination;
}

// Para seção.
int package::getSession() {
    return this->session;
}

// Para o topo da rota.
int package::getTop() {
    return this->route.top();
}

// FIM DOS GETTERS.

// Método para checar se a rota está vazia, ou seja, se o pacote chegou ao destino ou não.
bool package::isRouteEmpty() const {
    return route.empty();
}

// Sobrecarga do operador '=', apenas assimila os elementos de other para o 'this'.
package& package::operator=(const package& other) {
    if (this != &other) {
        ID = other.ID;
        origin = other.origin;
        destination = other.destination;
        arrivalTime = other.arrivalTime;
        timeStored = other.timeStored;
        timeTransported = other.timeTransported;
        route = other.route;
        session = other.session;
    }
    return *this;
}