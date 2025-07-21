#ifndef CONSULTATION_HPP
#define CONSULTATION_HPP

// Código responsável pela definição da classe de consultas.

#include <string>
#include <stdio.h>

class consultation {
    private:
        // Atributos que as consultas (CL e PC) podem possuir.
        int dateTime;
        std::string type;
        std::string name;
        int packageID;

    public:
        // Construtores sobrecarregados para ambos os tipos de consulta, além do padrão para permitir a criação de vectors de 'consultations'.
        // Construtor padrão.
        consultation();

        // Construtor parametrizado para consultas do tipo CL.
        consultation(int _dateTime, std::string _type, std::string _name);

        //Construtor parametrizado para consultas do tipo PC.
        consultation(int _dateTime, std::string _type, int _packageID);

        // Método para auxiliar no print das informações de uma consulta.
        void printConsultation();

        // Métodos getters que serão utilizado para auxiliar na busca.
        std::string getName();
        int getPackageID();
};

#endif