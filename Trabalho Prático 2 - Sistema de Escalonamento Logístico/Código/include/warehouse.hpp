#ifndef WAREHOUSE_HPP
#define WAREHOUSE_HPP

#include "stack.hpp" //vector
#include "package.hpp"

// Classe que define a estrutura do armazém, com varias seções formadas por pilhas, mantendo a lógica LIFO desejada.

class warehouse {
    private:
        // Atributo único, uma coleção de pilhas de pacotes para simular as diversas seções.
        vector<stack<package>> sessions;
    
    public:
        // Método que adiciona uma seção ao armazém, será chamado apenas na main.
        void addSession();
        
        // Método para adicionar um pacote, que estará carregando as informações necessárias para seu armazenamento.
        void storePackage(package& pac);
        
        // Método que remove um pacote de uma determinada seção e retorna uma referência ao pacote em questão.
        package& removePackageFor(int destination);
        
        // Método que testa se há algum pacote para 'destination'.
        bool hasPackageFor(int destination);
};

#endif