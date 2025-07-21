#ifndef INDEX_HPP
#define INDEX_HPP

// Arquivo para definição das structs responsáveis pelos índices.

#include "event.hpp"
#include "consultation.hpp"
#include "vector.hpp"
#include <string>

// Struct para definição do índice dos pacotes. Eles serão o cerne das consultas, por que armazenarão os índices dos eventos, já que todo evento tem um pacote associado a ele.
struct packageIndex {
    // Atributos para definição do índice, a chave será o ID do pacote.
    int packageID;
    vector<int> eventIndexes;

    // Sobrecarga dos operadores para viabilizar a montagem de uma árvore de índices de pacote.
    bool operator<(const packageIndex& other) const {
        return packageID < other.packageID;
    }
    bool operator==(const packageIndex& other) const {
        return packageID == other.packageID;
    }
    bool operator>(const packageIndex& other) const {
        return packageID > other.packageID;
    }

    // Construtores, padrão para viabilizar a criação de árvores e vetores, e parametrizado, para facilitar buscas.
    packageIndex();
    packageIndex(int _packageID) : packageID(_packageID) {}
};

// Struct para definição do índice dos clientes. Para manter a exigência de os eventos estarem apenas em um lugar, este índice possuis índices dos pacotes relacionados aos clientes.
struct clientIndex {
    // Atributos para definição do índice, a chave será o nome do cliente.
    std::string name;
    vector<int> relatedPackageIDs;

    // Sobrecarga dos operadores para viabilizar a criação de uma árvore de índices.
    bool operator<(const clientIndex& other) const {
        return name < other.name;
    }
    bool operator>(const clientIndex& other) const {
        return name > other.name;
    }
    bool operator==(const clientIndex& other) const {
        return name == other.name;
    }

    // Construtores padrão e parametrizado, para viabilizar a construção de árvores, inserção e busca.
    clientIndex();
    clientIndex(std::string _name) : name(_name) {}
};

#endif