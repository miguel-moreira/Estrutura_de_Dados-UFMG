// Código para a implementação dos métodos da classe 'consultationation', definidos em 'consultationation.hpp'.
#include "consultation.hpp"

// Construtor padrão.
consultation::consultation() {
    this->dateTime = -1;
    this->type = "null";
    this->name = "null";
    this->packageID = -1;
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

// Método para printar as informações de uma consulta.
void consultation::printConsultation() {
    fprintf(stdout,"%.6d %s ", dateTime, type.c_str());
    
    if (type == "CL") {
        fprintf(stdout, "%s\n", name.c_str());
    } else {
        fprintf(stdout, "%.3d\n", packageID);
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