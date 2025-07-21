// Código main, responsável pela leitura dos dados inicias e chamada do simulador.
#include <fstream> // Manipulação de arquivos.
#include "../include/simulator.hpp" // Inclui todos os outros arquivos mesmo que indiretamente.

int main(int argc, char* argv[]) {
    // Teste para checar se o arquivo de entrada foi passado na linha de comando.
    if (argc < 2) {
        fprintf(stderr, "Missing parameters at commmand line");
        return 1;
    }

    // Teste para checar se o arquivo foi devidamente aberto.
    std::fstream file(argv[1]);
    if (!file.is_open()) {
        fprintf(stderr, "Error opening file: %s\n",argv[1]);
        return 1;
    }

    // Variáveis que serão populadas por dados dos arquivos e posteriormente serão inseridas em uma instância
    // De 'parameters'.
    int transportCapacity, transportLatency, transportInterval, removalCost, numWarehouses, numPackages;
    vector<vector<int>> warehouseSchema;

    file >> transportCapacity;
    file >> transportLatency;
    file >> transportInterval;
    file >> removalCost;
    file >> numWarehouses;

    // Criação do escalonador e dos armazéns que serão utilizados no simulador.
    scheduler mainScheduler;
    vector<warehouse> warehouses(numWarehouses);
    for (int i = 0; i < numWarehouses; i++) {
        for (int j = 0; j < numWarehouses; j++) {
            warehouses[i].addSession();
        }
    }
    
    // Criação do vector para armazenar pacotes e instanciação do simulador.
    vector<package> packages;
    simulator mainSimulator;

    int auxCoord;
    vector<int> vectorAux;
    for (int i = 0; i < numWarehouses; i++) {
        vectorAux.clear();
        for (int j = 0; j < numWarehouses; j++) {
            file >> auxCoord;
            if (auxCoord) {
                vectorAux.push_back(j);
            }
        }
        
        // Criação da matriz de adjacência a partir dos dados do arquivo.
        warehouseSchema.push_back(vectorAux);
    }

    file >> numPackages;

    // Instanciação de parameters.
    parameters param(transportCapacity, transportLatency, transportInterval, removalCost, numWarehouses, warehouseSchema, numPackages);
    
    int arrivalTime, packageCode, origin, destination;
    std::string s_package, s_origin, s_destination;
    for (int i = 0; i < numPackages; i++) {
        file >> arrivalTime >> s_package >> packageCode >> s_origin >> origin >> s_destination >> destination;
        
        // Leitura dos pacotes e inserção deles no vector packages.
        package pac(i, origin, destination, arrivalTime);
        packages.push_back(pac);
    }   

    // Fechando arquivo
    file.close();
    
    // Chamadando o simulador discreto de eventos.
    mainSimulator.preSimulation(mainScheduler, warehouses, packages, param);
    mainSimulator.runSimulation(mainScheduler, warehouses, packages, param);

    return 0;
}