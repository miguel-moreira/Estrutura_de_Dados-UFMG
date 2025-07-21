#ifndef ENGINE_HPP
#define ENGINE_HPP

// Código responsável pela definição da classe principal do trabalho, a classe responsável por realizar as buscas e armazenar as informações de forma eficiente.

#include "avltree.hpp" // algorithms, fprintf.
#include "index.hpp" // event, consultation, string, vector.
#include <sstream>

class engine {
    private:
        // Atributos respinsáveis por armazenar e facilitar as buscas, árvores binárias de índices e vector de eventos.
        tree<packageIndex> packagesTree;
        tree<clientIndex> clientsTree;
        vector<event> allEvents;

        // Método principal para processamento de eventos, irá direcionar o evento para a construção correta.
        void processEvent(std::stringstream& ss, int dateTime);
        
        // Método principal para processamento de consultas e será responsável por direcionar a consulta ao lugar correto.
        void processConsultation(std::stringstream& ss, int dateTime, const std::string& consultationType);

        // Método para lidar com uma consulta do tipo CL.    
        void handleClientConsultation(consultation& clientConsultation);

        // Método para lidar com uma consulta do tipo PC.
        void handlePackageConsultation(consultation& packageConsultation);

        // Método EXTRA.
        // Método para lidar com uma consulta do tipo IT.
        void handleTimeIntervalConsultation(consultation& timeIntervalConsultation);

        // Método para lidar com eventos do tipo RG, que envolvem o registro de pacotes e de clientes.
        void handleRegistrationEvent(event& regEvent);

        // Método para lidar com outros tipos de evento, que envolvem apenas atualização de dados em pacotes.
        void handleOtherEvent(event& otherEvent);

        // Método EXTRA
        // Método de uma busca binária do tipo lowerBound, retorna o menor índice de 'target' no array.
        int LBbinarySearch(vector<event>& array, int target);

    public:
        // Construtor e destrutor padrões, que irão delegar ao construtor e destrutor da árvore binária e dos índices.
        engine();
        ~engine();

        // Método responsável por processar uma linha, será o único público enquanto os outros serão internos, já que irão ter contato direto com os atributos, e queremos manter o encapsulamento.
        void processLine(const std::string& line);
};

#endif
