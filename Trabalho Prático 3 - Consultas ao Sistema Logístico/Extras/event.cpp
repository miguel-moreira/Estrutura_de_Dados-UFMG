// Código para a implementação dos métodos da classe 'event', definidos em 'event.hpp'.
#include "event.hpp"

// Construtor padrão.
event::event() {
    this->dateTime = -1;
    this->type = "null";
    this->packageID = -1;
    this->sender = "null";
    this->receiver = "null";
    this->originWarehouse = -1;
    this->destinationWarehouse = -1;
    this->destinationSession = -1;
}

// Construtor para os eventos do tipo RG.
event::event(int _dateTime, std::string _type, int _packageID, std::string _sender, std::string _receiver, int _originWarehouse, int _destinationWarehouse) {
    this->dateTime = _dateTime;
    this->type = _type;
    this->packageID = _packageID;
    this->sender = _sender;
    this->receiver = _receiver;
    this->originWarehouse = _originWarehouse;
    this->destinationWarehouse = _destinationWarehouse;
}

// Construtor para os eventos dos tipos AR, RM, UR e TR. 
// Como o número de variáveis recebidas entre estes eventos é o mesmo e são todas do mesmo tipo, o construtor é o mesmo. A nomeação da variável foi feita pensando, antes de 'OR', são eventos do tipo AR, RM, UR, depois, eventos do tipo TR.
event::event(int _dateTime, std::string _type, int _packageID, int _destinationORoriginWarehouse, int _destinationSessionORWarehouse) {
    this->dateTime = _dateTime;
    this->type = _type;
    this->packageID = _packageID;
    
    if (_type != "TR") { // AR, RM, UR.
        this->destinationWarehouse = _destinationORoriginWarehouse;
        this->destinationSession = _destinationSessionORWarehouse;
    } else { // TR.
        this->originWarehouse = _destinationORoriginWarehouse;
        this->destinationWarehouse = _destinationSessionORWarehouse;
    }
}

// Construtor para eventos do tipo EN.
event::event(int _dateTime, std::string _type, int _packageID, int _destinationWarehouse) {
    this->dateTime = _dateTime;
    this->type = _type;
    this->packageID = _packageID;
    this->destinationWarehouse = _destinationWarehouse;
}

// Método para printar as informações de um determinado evento. Para o caso de o evento ser TR, 'destinationWarehouse' e 'destinationSession' servem como 'originWarehouse' e 'destinationWarehouse', respectivamente.
void event::printEvent() {
    fprintf(stdout, "%.7d EV %s %.3d ", dateTime, type.c_str(), packageID);

    if (type == "RG") {
        fprintf(stdout, "%s %s %.3d %.3d\n", sender.c_str(), receiver.c_str(), originWarehouse, destinationWarehouse);
    } else if (type == "EN") {
        fprintf(stdout, "%.3d\n", destinationWarehouse);
    } else if (type == "TR") {
        fprintf(stdout, "%.3d %.3d\n", originWarehouse, destinationWarehouse);
    } else { // AR, RM, UR.
        fprintf(stdout, "%.3d %.3d\n", destinationWarehouse, destinationSession);
    }
}

// Método getter para o remetente de um evento RG.
std::string event::getSender() {
    if (this->type == "RG") {
        return this->sender;
    } 
    return "";
}

// Método getter para o destinatário de um evento RG.
std::string event::getReceiver() {    
    if (this->type == "RG") {
        return this->receiver;
    }
    return "";
}

// Método getter para o ID do pacote de um evento.
int event::getPackageID() {
    return this->packageID;
}

// Método EXTRA.
// Método getter para o dateTime de um evento.
int event::getDateTime() {
    return this->dateTime;
}

// Sobrecarga do operador '<', retorna se um tempo é menor do que o outro.
bool event::operator<(const event& other) {
    if (this->dateTime != other.dateTime) {
        return this->dateTime < other.dateTime;
    } 
    return this->packageID < other.packageID;
}

// Sobrecarga do operador '>', retorna se um tempo é maior do que o outro.
bool event::operator>(const event& other) {
    if (this->dateTime != other.dateTime) {
        return this->dateTime > other.dateTime;
    } 
    return this->packageID > other.packageID;
}

// Sobrecarga do operador '<=', retorna se um tempo é menor ou igual do que o outro.
bool event::operator<=(const event& other) {
    if (this->dateTime != other.dateTime) {
        return this->dateTime <= other.dateTime;
    } 
    return this->packageID <= other.packageID;
}

// Sobrecarga do operador '>=', retorna se um tempo é maior ou igual do que o outro.
bool event::operator>=(const event& other) {
    if (this->dateTime != other.dateTime) {
        return this->dateTime >= other.dateTime;
    } 
    return this->packageID >= other.packageID;
}
