// Código para a implementação dos métodos da classe 'consultationation', definidos em 'consultationation.hpp'.
#include "consultation.hpp"

// Construtor padrão.
consultation::consultation() {
    this->dateTime = -1;
    this->type = "null";
    this->name = "null";
    this->packageID = -1;
    this->start = -1;
    this->end = -1;
}

// Construtor para consultationas do tipo CL.
consultation::consultation(int _dateTime, std::string _type, std::string _name) {
    this->dateTime = _dateTime;
    this->type = _type;
    this->name = _name;
}

// Construtor para consultas do tipo PC.
consultation::consultation(int _dateTime, std::string _type, int _packageID) {
    this->dateTime = _dateTime;
    this->type = _type;
    this->packageID = _packageID;
}

// Método EXTRA
// Construtor para consultas do tipo IT.
consultation::consultation(int _dateTime, std::string _type, int _start, int _end) {
    this->dateTime = _dateTime;
    this->type = _type;
    this->start = _start;
    this->end = _end;
}

// Atualizado para o EXTRA
// Método para printar as informações de uma consulta.
void consultation::printConsultation() {
    fprintf(stdout,"%.6d %s ", dateTime, type.c_str());
    
    if (type == "CL") {
        fprintf(stdout, "%s\n", name.c_str());
    } else if (type == "PC"){
        fprintf(stdout, "%.3d\n", packageID);
    } else {
        fprintf(stdout, "%.7d %.7d\n", start, end);
    }
}

// Método getter que retorna o nome do cliente associado à consulta. Válido para consultas do tipo CL.
std::string consultation::getName() {
    if (this->type == "CL") {
        return this->name;
    } 
    return "";
}

// Método getter para retornar o ID do pacote associado à consulta. Válido para consultas do tipo PC.
int consultation::getPackageID() {
    if (this->type == "PC") {
        return this->packageID;
    }
    return -1;
}

// Método EXTRA
// Método getter para retornar o 'start'. Válido para consultas do tipo IT.
int consultation::getStart() {
    if (this->type == "IT") {
        return this->start;
    }
    return -1;
}   

// Método EXTRA
// Método getter para retornar o 'end'. Válido para consultas do tipo IT.
int consultation::getEnd() {
    if (this->type == "IT") {
        return this->end;
    }
    return -1;
}
