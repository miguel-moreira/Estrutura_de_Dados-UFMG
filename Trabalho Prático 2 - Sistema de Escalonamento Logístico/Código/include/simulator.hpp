#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "scheduler.hpp" //heap
#include "warehouse.hpp" //packages, stack, vector
#include "eventandparameters.hpp" 
#include "algorithms.hpp" //BFS

// Classe central da simulação, responsável por coordenar todos os principais elementos do sistema de entregas.
// Foi implementada como uma classe de métodos, a fim de facilitar a modularização do código.

class simulator {
    private:
        // Métodos privados, utilizados como auxílio para os métodos públicos principais.
        
        // Método usado para calcular a rota de cada um dos pacotes no grafo.
        void calculateAllRoutes(vector<package>& packages, parameters& param);

        // Método que faz o cálculo do tempo dos eventos.
        int nextTranspTime(int time, parameters& param);
        
        // Método para agendar os primeiros eventos de armazenamento dos pacotes.
        void scheduleInitialStorageEvents(scheduler& eventScheduler, vector<package>& packages);
        
        // Método responsável por processar um evento do tipo um, armazenamento.
        void processStorageEvent(event& currentEvent, scheduler& eventScheduler, vector<warehouse>& warehouses, vector<package>& packages, parameters& param);

        // Método responsável por processar um evento do tipo dois, transporte.
        void processTransportEvent(event& currentEvent, scheduler& eventScheduler, vector<warehouse>& warehouses, parameters& param);

    public:
        // Método que será chamado para realizar os processos iniciais, da formação incial do heap e consequentemente dos transportes.
        void preSimulation(scheduler& eventScheduler, vector<warehouse>& warehouses, vector<package>& packages, parameters& param);

        // Método principal da simulação, será o último a acontecer e depende de todos os anteriores para funcionar corretamente.
        void runSimulation(scheduler& eventScheduler, vector<warehouse>& warehouses, vector<package>& packages, parameters& param);

};

#endif