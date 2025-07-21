// Código main, responsável por fazer as chamadas das funções para determinar os limiares ideais.
#include "ordenadoruniversal.hpp" //todas citadas nos outros arquivos inclusas
#include <fstream> //std::ifstream

// Struct para facilitar o armazenamento dos dados que serão lidos do arquivo.
typedef struct {
    int seed;
    double limiarCusto;
    double a, b, c;
    int tam;
} parametros;

int main(int argc, char* argv[]) {
    // Teste para checar se o arquivo foi passado na linha de comando.
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo_entrada>\n", argv[0]);
        return 1;
    }
    
    // Instanciação da classe ordenadoruniversal para poder acessar os métodos.
    ordenadoruniversal<int> ordenadorInt;
    vector<int> vetor; // Armazenar o vetor original lido do arquivo

    // Teste para checar se o arquivo foi devidamente aberto.
    std::ifstream arquivo(argv[1]);
    if (!arquivo.is_open()) {
        fprintf(stderr, "Erro ao abrir o arquivo: %s\n", argv[1]);
        return 1;
    }

    // Instanciação dos parâmetros, sua leitura e preenchimento dos TADs 'estatisticas' e 'vector'.
    parametros param;

    arquivo >> param.seed;
    arquivo >> param.limiarCusto;
    arquivo >> param.a;
    arquivo >> param.b;
    arquivo >> param.c;
    arquivo >> param.tam;

    estatisticas estat(param.a, param.b, param.c);

    int elementoAux;
    for (int i = 0; i < param.tam; ++i) {
        arquivo >> elementoAux;
        vetor.push_back(elementoAux);
    }

    // Fechamento da stream do arquivo após o fim da leitura dos elementos.
    arquivo.close();
    
    int numQuebras = ordenadorInt.numeroQuebras(vetor);

    fprintf(stdout, "size %d", vetor.tamanho());
    fprintf(stdout, " seed %d", param.seed);     
    fprintf(stdout, " breaks %d\n", numQuebras);

    // CALIBRAÇÃO: DETERMINAR LIMIARES
    int limiarParticaoTarget = ordenadorInt.determinaLimiarParticao(vetor, param.limiarCusto, estat);

    int limiarQuebrasTarget = ordenadorInt.determinaLimiarQuebras(vetor, param.limiarCusto, estat, limiarParticaoTarget, param.seed);

    return 0;
}