#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include "stack.hpp" //vector

// Classe responsável por definir e operar sobre os pacotes a serem transportados.

class package {
    private:
        // Atributos simples que serão populados assim que forem lidos na main.
        int ID; // ID do pacote.
        int origin; // Armazém de origem do pacote.
        int destination; // Armazém final do pacote.

        int arrivalTime; // Tempo em que o pacote chegou no armazém de origem.
        int timeStored; // Tempo total que o pacote passou armazenado.
        int timeTransported; // Tempo total que o pacote passou sendo transportado.

        stack<int> route; // Rota do pacote, o caminho entre os armazéns a ser seguido.
        int session; // Seção em que o pacote será armazenado no armazém.
    
    public:
        // Construtor e destrutores padrão, além do construtor parametrizado e construtor de cópia.
        package();
        package(int _ID, int _origin, int _destination, int _arrivalTime);
        package(const package& other);
        ~package();

        // Método para avançar a posição da rota do pacote.
        void advanceRoute();
        
        // Método que, depois de avançada a rota, ajusta a seção que o pacote irá ser armazenado.
        void adjustSession();
        
        // Método Setter para a rota, que é calculada depois da inserção do pacote no armazém de origem.
        void setRoute(stack<int>& _route);

        // Método para adicionar tempo transportado e facilitar a sua manipulação.
        void addTimeTransported(int time);
        
        // Método para adicionar tempo armazenado e facilitar a sua manipulação.
        void addTimeStored(int time);

        // Métodos Getters para todos os atributos do pacote.
        int getID();
        int getArrivalTime();
        int getTimeStored();
        int getTimeTransported();
        int getOrigin();
        int getDestination();
        int getSession();
        int getTop();

        // Método para checar se a pilha que armazena a rota está vazia.
        bool isRouteEmpty() const;
        
        // Sobrecarga do operador '=', para permitir que pacotes sejam atribuídos entre si..
        package& operator=(const package& other);
};

#endif