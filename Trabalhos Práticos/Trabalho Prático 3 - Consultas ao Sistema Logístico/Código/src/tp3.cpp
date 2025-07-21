// Código main, responsável por ler as informações do arquivo e processar as consultationas.
#include <fstream> // Usado para manipulação do arquivo.
#include "engine.hpp"

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

    // Instanciação da engine, responsável por todo sistema de consultas.
    engine eng;

    // Leitura do arquivo linha por linha, o processamento será feito internamente na engine.
    std::string line;
    while (std::getline(file,line)) {
        eng.processLine(line);
    }

    // Fechando o arquivo.
    file.close();

    return 0;
}