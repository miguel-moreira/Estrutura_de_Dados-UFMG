// Arquivo que contém a implementação dos métodos definitos em 'simulator.hpp'
#include "../include/simulator.hpp"

// Inicialização de variáveis globais para fazer o monitoramento dos eventos, 'start' será um valor único, 
// Correspondente ao tempo de chegada do primeiro pacote em seu armazém de origem.
// Durante todo o código e 'packagesDelivered' será importantíssimo para o loop principal.
int start = 0;
int packagesDelivered = 0;

// Método para o cálculo das rotas de cada pacote, itera sobre o vector de pacotes e para cada um deles roda a BFS,
// Criando a rota e a settando no pacote.
void simulator::calculateAllRoutes(vector<package>& packages, parameters& param) {
    try {
        for (int i = 0; i < packages.size(); i++) {
            stack<int> route;
            route = BFS(param.warehouseSchema, packages[i].getOrigin(), packages[i].getDestination());
            packages[i].setRoute(route);
            packages[i].adjustSession();
        }
    } catch (...) {
        fprintf(stderr, "Error in calculateAllRoutes.\n");
    }
}

// Método do cálculo do próximo tempo de transporte a ser agendado. 
// Seu funcionamento depende do tempo do evento atual e da variável global 'start'.
int simulator::nextTranspTime(int time, parameters& param) {
    int x = time - start;
    x /= param.transportInterval;
    x++;
    return start + x * param.transportInterval;
}

// Método responsável para inicializar o heap de eventos, com os eventos de armazenamento inciais,
// Que ocorrem antes de qualquer transporte, entçao para cada pacote, um evento é agendado.
void simulator::scheduleInitialStorageEvents(scheduler& eventScheduler, vector<package>& packages) {
    try {
        for (int i = 0; i < packages.size(); i++) {
            event storageEvent(packages[i].getArrivalTime(), 1, packages[i].getID());
            eventScheduler.insertEvent(storageEvent);
        }
    } catch (...) {
        fprintf(stderr, "Error in scheduleInitialStorageEvents.\n");
    }
}

// Metódo que processa um evento de armazenamento. Primeiramente, acha o pacote que está sendo armazenado e checa se ele está no destino ou não,
// Caso esteja, registra a entrega, caso contrário, agenda o próximo evento de transporte se a seção estiver vazia (porque o contrário significa
// que já há um evento de transporte agendado para a seção em questão), e atualiza a rota e seção do pacote.
void simulator::processStorageEvent(event& currentEvent, scheduler& eventScheduler, vector<warehouse>& warehouses, vector<package>& packages, parameters& param) {
    try {
        package& pac = packages[currentEvent.packageID];
    
        pac.addTimeTransported(param.transportLatency);
    
        if (pac.getSession() == -1) {
            fprintf(stdout, "%.7d pacote %.3d entregue em %.3d\n", currentEvent.time, pac.getID(), pac.getDestination());
            packagesDelivered++;
            return;
        } else {
            int currentWarehouse = pac.getTop();
            int sess = pac.getSession();
    
            int x = nextTranspTime(currentEvent.time, param);
    
            if (!warehouses[currentWarehouse].hasPackageFor(pac.getSession())) {
                event transportEvent(x, 2, currentWarehouse, sess);
                eventScheduler.insertEvent(transportEvent); 
            }
    
            warehouses[currentWarehouse].storePackage(pac);
            
            fprintf(stdout, "%.7d pacote %.3d armazenado em %.3d na secao %.3d\n", currentEvent.time, pac.getID(), currentWarehouse, pac.getSession());
    
            pac.advanceRoute();
            pac.adjustSession();
        }
    } catch (...) {
        fprintf(stderr, "Error in processStorageEvent.\n");
    }
}   

// Método responsável por processar um evento de transporte. Primeiramente, é necessário pegar os (capacidade) primeiros elementos da seção,
// Então vetores adicionados são usados para armazenar os pacotes desempilhados. Passada esta parte, caso pacotes tenham sobrado, eventos para
// O próximo transporte são agendados, e para os pacotes a serem transportados eventos de armazenamento são agendados. Ao fim, os pacotes que 
// Não couberam no transporte são rearmazenados.
void simulator::processTransportEvent(event& currentEvent, scheduler& eventScheduler, vector<warehouse>& warehouses, parameters& param) {
    try {
        int origin = currentEvent.origin;
        int destination = currentEvent.destination;
    
        vector<package> toTransport, toRestore, tempStack;
    
        while (warehouses[origin].hasPackageFor(destination)) {
            package& pac = warehouses[origin].removePackageFor(destination);
            currentEvent.time += param.removalCost;
            
            pac.addTimeStored(currentEvent.time - pac.getArrivalTime());
    
            fprintf(stdout, "%.7d pacote %.3d removido de %.3d na secao %.3d\n", currentEvent.time, pac.getID(), pac.getTop(), pac.getSession());
            
            tempStack.push_back(pac);
        }
    
        for (int i = tempStack.size() - 1; i >= 0; i--) {
            if (toTransport.size() < param.transportCapacity) {
                toTransport.push_back(tempStack[i]);   
            } else {
                toRestore.push_back(tempStack[i]);
            }
        }
        
        if (toRestore.size() > 0) {
            int x = nextTranspTime(currentEvent.time, param);
            event transportEvent(x,2,origin,destination);
            eventScheduler.insertEvent(transportEvent);
        }
    
        for (int i = 0; i < toTransport.size(); i++) {
            package& pac = toTransport[i];  
    
            fprintf(stdout, "%.7d pacote %.3d em transito de %.3d para %.3d\n", currentEvent.time, pac.getID(), pac.getTop(), pac.getSession());
    
            event arrivalEvent(currentEvent.time + param.transportLatency, 1, pac.getID());
            eventScheduler.insertEvent(arrivalEvent);
        }
    
        for (int i = 0; i < toRestore.size(); i++) {
            warehouses[origin].storePackage(toRestore[i]);
            package& pac = toRestore[i];
            fprintf(stdout, "%.7d pacote %.3d rearmazenado em %.3d na secao %.3d\n", currentEvent.time, toRestore[i].getID(), pac.getTop(), pac.getSession());
        }
    } catch (...) {
        fprintf(stderr, "Error in processTransportEvent.\n");
    }
}

// Método que será chamado na main responsável por inicializar o heap e prepara-lo para o loop principal, 
// Preparando os pacotes, inicializando a variável global 'start', utilizada
// Finalizada esta parte, o código estará preparado para começar a simulação discreta de eventos.
void simulator::preSimulation(scheduler& eventScheduler, vector<warehouse>& warehouses, vector<package>& packages, parameters& param) {
    try {
        start = packages[0].getArrivalTime();
        calculateAllRoutes(packages, param);
        scheduleInitialStorageEvents(eventScheduler, packages);
    } catch (...) {
        fprintf(stderr, "Error in preSimulation.\n");
    }
}

// Método responsável por coordenar os outros, passada a 'preSimulation', o heap 'eventScheduler' estará preparado para começar o loop,
// A cada iteração um evento é removido e possivelmente adicionado no processo. A simulação irá acabar apenas quando o heap estiver vazio
// e todos os pacotes terem sido entregues.
void simulator::runSimulation(scheduler& eventScheduler, vector<warehouse>& warehouses, vector<package>& packages, parameters& param) {
    try {
        while (!eventScheduler.empty() and packagesDelivered < packages.size()) {
            event currentEvent = eventScheduler.removeEvent();
    
            if (currentEvent.type == 1) {
                processStorageEvent(currentEvent, eventScheduler, warehouses, packages, param);
            } else if (currentEvent.type == 2) {
                processTransportEvent(currentEvent, eventScheduler, warehouses, param);
            }
        }
    } catch (...) {
        fprintf(stderr, "Error in runSimulation.\n");
    }
}