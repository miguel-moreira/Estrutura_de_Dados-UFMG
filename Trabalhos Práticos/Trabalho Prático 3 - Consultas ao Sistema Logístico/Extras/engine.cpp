// Código responsável pela implementação dos métodos definidos em 'engine.hpp'.
#include "engine.hpp"

// Construtor padrão, irá delegar aos construtores declarados nas estruturas de dados internas dos atributos.
engine::engine() {}

// Destrutor padrão, também irá delegar ao destrutor interno das estruturas.
engine::~engine() {}

// Método público que será chamado na main, responsável pela administração geral das informações lidas no arquivo, direcionando o conteúdo para os locais corretos. Checa se é um evento ou uma consulta e manda para funções auxiliares.
void engine::processLine(const std::string& line) { 
    int dateTime;
    std::string type;
    
    std::stringstream ss(line);
    ss >> dateTime >> type;

    if (type == "EV") {
        processEvent(ss, dateTime);
    } else {
        processConsultation(ss, dateTime, type);
    }
}

// Método privado auxiliar para o processamento de eventos.
void engine::processEvent(std::stringstream& ss, int dateTime) {
    std::string eventType;
    int packageID;

    ss >> eventType >> packageID;
    if (eventType == "RG") {
       std::string sender, receiver;
       int originWarehouse, destinationWarehouse;
       ss >> sender >> receiver >> originWarehouse >> destinationWarehouse;

       event regEvent(dateTime, eventType, packageID, sender, receiver, originWarehouse, destinationWarehouse);
       handleRegistrationEvent(regEvent);
    } else if (eventType == "EN") {
        int destinationWarehouse;
        ss >> destinationWarehouse;

        event enEvent(dateTime, eventType, packageID, destinationWarehouse);
        handleOtherEvent(enEvent);
    } else { // AR, RM, UR e TR.
        int destORorigWarehouse, destSessORWarehouse;
        ss >> destORorigWarehouse >> destSessORWarehouse;
            
        event flexEvent(dateTime, eventType, packageID, destORorigWarehouse, destSessORWarehouse);
        handleOtherEvent(flexEvent);
    }
}

// Método privado auxiliar para o processamento de consultas.
void engine::processConsultation(std::stringstream& ss, int dateTime, const std::string& consultationType) {
    if (consultationType == "CL") {
        std::string clientName;
        ss >> clientName;

        consultation clientConsultation(dateTime, consultationType, clientName);
        handleClientConsultation(clientConsultation);
    } else if (consultationType == "PC") {
        int packageID;
        ss >> packageID;

        consultation packageConsultation(dateTime, consultationType, packageID);
        handlePackageConsultation(packageConsultation);
    } else {
        int start, end;
        ss >> start >> end;

        consultation timeIntervalConsultation(dateTime, consultationType, start, end);
        handleTimeIntervalConsultation(timeIntervalConsultation);
    }
}

// Método responsável pelas saídas das consultas do tipo CL, mostrando os primeiros e últimos eventos associados aos pacotes relacionados a um determinado cliente. 
// Irá primeiro checar se a consulta está correta e depois encontrará o cliente na árvore a partir do índice de cliente, tendo assim acesso aos índices dos pacotes relacionados, e viabilizando o print.
void engine::handleClientConsultation(consultation& clientConsultation) {
    try {
        std::string aux = clientConsultation.getName();
        if (aux != "") {
            node<clientIndex>* clientNode = clientsTree.find(clientIndex(aux));
            
            clientConsultation.printConsultation();
            if (!clientNode) {
                fprintf(stdout, "0\n");
                return;
            }
    
            vector<event> lastEvents;
            clientIndex* clientData = &clientNode->data;
            fprintf(stdout, "%d\n", clientData->relatedPackageIDs.size() * 2);
    
            for (int i = 0; i < clientData->relatedPackageIDs.size(); i++) {
                int currentPackageID = clientData->relatedPackageIDs[i];
                node<packageIndex>* packageNode = packagesTree.find(packageIndex(currentPackageID));
                
                if(packageNode and packageNode->data.eventIndexes.size() > 0) {
                    int firstEventIndex = packageNode->data.eventIndexes[0];
                    allEvents[firstEventIndex].printEvent();
                    
                    int lastEventIndex = packageNode->data.eventIndexes[packageNode->data.eventIndexes.size() - 1];
                    lastEvents.push_back(allEvents[lastEventIndex]);
                }
            }
    
            if (lastEvents.size() > 0) {
                mergeSort(lastEvents, 0, lastEvents.size() - 1);
                for (int j = 0; j < lastEvents.size(); j++) {
                    lastEvents[j].printEvent();
                }
            }
    
        } else {
            fprintf(stdout, "This consult does not have a name associated with it.\n");
        }
        
        return;
    } catch (...) {
        fprintf(stderr, "Error in handleClientConsultation().\n");
    }
}

// Método responsável pelas saídas das consultas do tipo PC, irá procurar na árvore de pacotes pelo ID fornecido na consulta, caso não exista apenas printa erro, mas caso contrário, encontra o pacote e itera sobre os eventos dele até o momento da consulta.
void engine::handlePackageConsultation(consultation& packageConsultation) {
    try {
        int aux = packageConsultation.getPackageID();
        if (aux != -1) {
            node<packageIndex>* packageNode = packagesTree.find(packageIndex(aux));
    
            packageConsultation.printConsultation();
            if (!packageNode) {
                fprintf(stdout, "package does %d not exist.\n", aux);
                return;
            }
    
            fprintf(stdout, "%d\n", packageNode->data.eventIndexes.size());
            for (int i = 0; i < packageNode->data.eventIndexes.size(); i++) {
                int eventIndex = packageNode->data.eventIndexes[i];
                allEvents[eventIndex].printEvent();
            }
        } else {
            fprintf(stdout, "This consult does not have a package associated with it.\n");
        }
        
        return;
    } catch (...) {
        fprintf(stderr, "Error in handlePackageConsultation().\n");
    }
}

// Método EXTRA
// Método responsável pelas sáidas do tipo IT. Irá fazer duas buscas binárias no vetor de eventos para pegar os índices de 'start' e 'begin'. Não restringe ao armazém.
void engine::handleTimeIntervalConsultation(consultation& timeIntervalConsultation) {
    try { 
        
        timeIntervalConsultation.printConsultation();
        int startIndex = timeIntervalConsultation.getStart();

        int lowerBound = LBbinarySearch(allEvents, startIndex), count = 0;
        for (int i = lowerBound; i < allEvents.size(); i++) {
            event& currentEvent = allEvents[i];

            if (currentEvent.getDateTime() > timeIntervalConsultation.getEnd()) {
                break;
            }
            count = i;
        }

        fprintf(stdout, "%d\n", count - 1);
        
        for (int i = lowerBound; i < allEvents.size(); i++) {
            event& currentEvent = allEvents[i];

            if (currentEvent.getDateTime() > timeIntervalConsultation.getEnd()) {
                break;
            }

            currentEvent.printEvent();
        }

    } catch (...) {
        fprintf(stderr, "Error in handleTimeIntervalConsultation.\n");
    }
}

// Método responsável por lidar com eventos do tipo RG, que exigem mais atenção já que eles possuem informação chave para as consultas, 
// os clientes e os pacotes relacionados a ele, então, ele age nas duas árvores atributo e no vector de eventos, 
// inserindo pacotes e clientes ao mesmo tempo que checa a existência deles. Para manter a exigência de os eventos estarem apenas em um lugar, 
// vamos manter todos os eventos no vector central 'allEvents'.
void engine::handleRegistrationEvent(event& regEvent) {
    try {
        allEvents.push_back(regEvent);
        int eventIndex = allEvents.size() - 1;

        packageIndex newPackage(regEvent.getPackageID());
        node<packageIndex>* packageNode = packagesTree.find(newPackage);

        if (!packageNode) {
            packagesTree.insert(newPackage);
            packageNode = packagesTree.find(newPackage);
        }
        
        if (!packageNode) return;
    
        packageNode->data.eventIndexes.push_back(eventIndex);
        
        int packageID = regEvent.getPackageID();

        clientIndex sender(regEvent.getSender());
        node<clientIndex>* senderNode = clientsTree.find(sender);
        if (!senderNode) {
            clientsTree.insert(sender);
            senderNode = clientsTree.find(sender);
        }
        if (senderNode) {
            senderNode->data.relatedPackageIDs.push_back(packageID);
        }
    
        clientIndex receiver(regEvent.getReceiver());
        node<clientIndex>* receiverNode = clientsTree.find(receiver);
        if (!receiverNode) {
            clientsTree.insert(receiver);
            receiverNode = clientsTree.find(receiver);
        }
        if (receiverNode) {
            receiverNode->data.relatedPackageIDs.push_back(packageID);
        }

    } catch (...) {
        fprintf(stderr, "Error in handleRegistrationEvent().\n");
    }
}

// Método responsável por lidar com os outros tipos de evento, que irão operar apenas sobre a árvore de pacotes e vector de eventos, atualizando suas informações.
void engine::handleOtherEvent(event& otrEvent) {
    try {
        allEvents.push_back(otrEvent);
        int eventIndex = allEvents.size() - 1;

        node<packageIndex>* packageNode = packagesTree.find(packageIndex(otrEvent.getPackageID()));
        if (packageNode) {
            packageNode->data.eventIndexes.push_back(eventIndex);
        }
    } catch (...) {
        fprintf(stderr, "Error in handleOtherEvent().\n");
    }
}

// Método EXTRA
// Método para que faz uma busca binária do tipo lowerbound, ou seja, pega o primeiro índice em que target aparece.
int engine::LBbinarySearch(vector<event>& array, int target) {
    int left = 0;
    int right = array.size() - 1;
    int targetPos = array.size(); 
   
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (array[mid].getDateTime() >= target) {
            targetPos = mid;
            right = mid - 1;
        } else {
            left = mid + 1;         
        }
    }

    return targetPos;
}
