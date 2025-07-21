#ifndef EVENT_HPP
#define EVENT_HPP

// Código responsável pela definição da classe de eventos.

#include <string>
#include <stdio.h>

class event {
    private:
        // Atributos do evento, suficientes para construir eventos dos seis tipos disponíveis.
        int dateTime;
        std::string type; //RG, AR, RM, UR, TR, EN
        int packageID;
        std::string sender;
        std::string receiver;
        int originWarehouse;
        int destinationWarehouse;
        int destinationSession;
    
    public:
        // Construtores, que serão sobrecarregados para que os diferentes tipos de evento possam ser montados, além do padrão, para viabilizar a criação de vectores e outras estruturas que poderão armazenar eventos.
        // Construtor padrão.
        event();

        // Construtor do evento RG.
        event(int _dateTime, std::string _type, int _packageID, std::string _sender, std::string _receiver, int _originWarehouse, int _destinationWarehouse);

        // Construtor dos eventos AR, RM, UR e TR.
        event(int _dateTime, std::string _type, int _packageID, int _destinationORoriginWarehouse, int _destinationSessionORWarehouse);

        // Construtor do evento EN.
        event(int _dateTime, std::string _type, int _packageID, int _destinationWarehouse);

        // Método para auxiliar no print das informações de um evento.
        void printEvent();

        // Métodos getters para auxiliar na busca.
        std::string getSender();
        std::string getReceiver();
        int getPackageID();

        // Sobrecarga dos operadores '<','>', '<=' e '>=' para viabilizar o sort entre eventos.
        bool operator<(const event& other);
        bool operator>(const event& other);
        bool operator<=(const event& other);
        bool operator>=(const event& other);
};

#endif