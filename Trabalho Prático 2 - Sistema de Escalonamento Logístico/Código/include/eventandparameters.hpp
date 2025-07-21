#ifndef EVENTANDPARAMETERS_HPP
#define EVENTANDPARAMETERS_HPP

#include "vector.hpp"

// Arquivo para implementação dos eventos e parâmetros usados em outras partes do código.

// Struct que armazena os dados coletados na main no arquivo de entrada.
struct parameters {
    
    //Dados armazenados:
    int transportCapacity; // Capacidade de transporte.
    int transportLatency; // Latência de transporte (duração do transporte).
    int transportInterval; // Intervalo entre transportes.
    int removalCost; // Custo de remoção de pacotes do armazém.
    int numWarehouses; // Número de armazéns.
    vector<vector<int>> warehouseSchema; // Matriz de adjacência dos armazéns.
    int numPackages; // Número de pacotes.

    // Construtor que recebe todos os dados e os inicializa.
    parameters(int _transportCapacity, int _transportLatency, int _transportInterval,
               int _removalCost, int _numWarehouses,
               vector<vector<int>> _warehouseSchema, int _numPackages)
        : transportCapacity(_transportCapacity),
          transportLatency(_transportLatency),
          transportInterval(_transportInterval),
          removalCost(_removalCost),
          numWarehouses(_numWarehouses),
          warehouseSchema(_warehouseSchema),
          numPackages(_numPackages)
    {}

};

// Struct responsável por definir os eventos.
struct event{
    int time; // Tempo de ocorrência do evento.
    int type; //Tipo do evento criado, 1 para armazenamento, 2 para transporte.
    int packageID; // ID do pacote do evento em questão, será usado para eventos de armazenamento apenas.
    int origin; // Origem do evento, de onde ele começa.
    int destination; // Destino do evento, para onde ele é direcionado.
    long long key; // Chave única do evento.

    // Construtor para eventos de armazenamento, em que o pacote é necessário, gera a 'key' com o tempo, ID e tipo.
    event(int _time, int _type, int _packageID)
        : time(_time),
          type(_type),
          packageID(_packageID),
          origin(0),
          destination(0),
          key((long long)_time * 10000000 + (long long)_packageID * 10 + 1)
    {}

    // Construtor para eventos de transporte, que precisam do destino e origem principalmente, gera a 'key' com tempo, origem, destino e tipo
    event(int _time, int _type, int _origin, int _destination)
        : time(_time),
          type(_type),
          packageID(-1), // Pacote não aplicável
          origin(_origin),
          destination(_destination),
          key((long long)_time * 10000000 + (long long)_origin * 100000 + (long long)_destination * 10 + 2)
    {}

    // Construtor padrão de eventos.
    event() : time(0), type(0), packageID(-1), origin(0), destination(0), key(0) {}
    
    // Sobrecarga do operador '<', necessário para comparar 2 eventos distintos e armazena-los corretamente no min-heap de eventos.
    bool operator<(const event& other) const {
        return key < other.key;
    }
};

#endif