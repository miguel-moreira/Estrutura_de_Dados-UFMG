#ifndef ORDENADORUNIVERSAL_HPP
#define ORDENADORUNIVERSAL_HPP

#include "sorts.hpp" //vector, estatisticas, cstdlib inclusos
#include <cmath>
#include <string>

// Esta classe fornece métodos para realizar uma "ordenação universal inteligente". Por ser um template, ela pode ordenar vetores de qualquer tipo de dado.
template<typename T>
class ordenadoruniversal {
    public:
        // Método que faz a seleção, a partir do 'minTamParticao' e 'limiarQuebras' do algoritmo ideal a ser utilizado.
        // Registra as estatísticas durante a execução utilizando o arquivo 'sorts.hpp' e 'estatisticas.hpp'.
        void ordenadorUniversal(vector<T>& vetor, int minTamParticao, estatisticas& estat, int limQuebras);

        // Método responsável por determinar qual é o menor tamanho possível de uma partição, sendo satélite para vários outros.
        // Será chamado na main para realizar as operações seguintes.
        int determinaLimiarParticao(vector<T>& vetor, double limiarCusto, estatisticas& estat);

        // Método responsável por determinar qual é o tamanho mínimo de quebras que um vetor pode ter.
        // Estas quebras são vitais para determinação de qual algoritmo de sort será utilizado.
        // Será chamado na main para realizar suas operações internas de calibração.
        int determinaLimiarQuebras(vector<T>& vetor, double limiarCusto, estatisticas& estat, int minTamParticao, int seed);

        // Método que será interno ao 'determinaLimiarParticao' e ao 'determinaLimiarQuebras' , pois será apenas chamado iterativamente para refinar as faixas de busca.
        // O objetivo é reduzir a busca para determinar o 'minTamParticao' e o 'limQuebras' o mais rápido possível.
        void calculaNovaFaixa(vector<int>& vetorMPS, vector<double>& custos, int limParticao, int& minMPS, int & maxMPS, int& passoMPS, int numMPS, float& diffCusto);

        // Função responsável por determinar o número de quebras no vetor, ou seja, quantas vezes o elemento na posição [i-1] é maior que o elemento da posição [i].
        int numeroQuebras(vector<T>& vetor);

        // Função auxiliar para fazer o print iterativo das estatísticas durante a execução.
        void imprimeEstatisticas(std::string sort, int t, vector<double>& custos, int numX, estatisticas& estat);
};

//IMPLEMENTAÇÃO DOS MÉTODOS

// Este método será chamado apenas depois de o 'minTamParticao' estar bem definido, caso contrário, o comportamento seria incorreto.
// Usando este dado, o método decide qual é o melhor ordenador a ser utilizado, tentando reduzindo o custo ao máximo.
template<typename T>
void ordenadoruniversal<T>::ordenadorUniversal(vector<T>& vetor, int minTamParticao, estatisticas& estat, int limQuebras) {
    try {
        int numQuebras = numeroQuebras(vetor);
	    if (vetor.tamanho() > minTamParticao) {
            if (numQuebras > limQuebras) {
		        mergeSort(vetor, 0,vetor.tamanho() - 1, estat);
	        } else {
		        quickSort(vetor, 0, vetor.tamanho() - 1, estat, minTamParticao);
	        }
        } else {
            insertionSort(vetor, 0, vetor.tamanho() - 1, estat);
        }
    } catch (...) {
        fprintf(stderr, "Erro durante a ordenação em ordenadorUniversal.\n");
    }
}

// O método trabalha com os índices e intervalos do vectorMPS, estabelecendo quais devem ser os novos índices de partição a serem analisados.
// Como ele recebe parâmetros por referência, o valor é alterado durante a sua execução e já usado na próxima iteração, o que justifica ser void.
// X pode se referir tanto a 'MPS' quanto a 'Quebras', porque o método é reutilizado em 'determinaLimiarParticao' e 'determinaLimiarQuebras'.
// Por fim, a alteração é feita escolhendo os 2 intervalos mais próximos ao target (menor custo), que posteriormente serão subdivididos novamente.
template<typename T>
void ordenadoruniversal<T>::calculaNovaFaixa(vector<int>& vetorX, vector<double>& custos, int limParticao, int& minX, int& maxX, int& passoX, int numX, float& diffCusto) {
    int novoMin, novoMax;
    if (limParticao == 0) {
        novoMin = 0;
        novoMax = 2;
    } else if (limParticao == numX - 1) {
        novoMin = numX - 3;
        novoMax = numX - 1;
    } else {
        novoMin = limParticao - 1;
        novoMax = limParticao + 1;
    }

    minX = vetorX[novoMin];
    maxX = vetorX[novoMax];
    passoX = (maxX - minX) / 5;
    if (!(passoX)) {
        passoX++;
    }

    diffCusto = std::fabs(custos[novoMin] - custos[novoMax]);
}

// O método é responsável por calcular o 'minTamParticao'(target), a fim de reduzir o custo para um número menor ou muito próximo do 'limiarCusto' recebido na main.
// Ele faz isso definindo o maior intervalo possível inicialmente (minMPS e maxMPS) e vai refinando o target a partir disto.
// O loop principal irá acabar quando o valor de custo ideal for batido ou quando o número de iterações ultrapassa 5, retornando um custo próximo do ideal.
// O loop interno é o responsável por gerar os prints desejados e percorrer o vector pelos intervalos de partição desejados
// Por fim, o 'calculaNovaFaixa' é chamado, para reduzir a faixa de busca, e é retornado o valor ideal, ou próximo, do 'minTamParticao'.
template<typename T>
int ordenadoruniversal<T>::determinaLimiarParticao(vector<T>& vetor, double limiarCusto, estatisticas& estat) {
    int minMPS = 2;
    int maxMPS = vetor.tamanho();
    int passoMPS = (maxMPS - minMPS) / 5;
    if (passoMPS == 0)
        passoMPS++;
    int numMPS = 0;

    int limParticao = 0;
    float diffCusto = 1e7;
    int iter = 0;

    vector<double> custos;
    vector<T>vetorAux;
    vector<int>vetorMPS;

    do {
        try {
            vetorMPS.limpar();
            custos.limpar();
            numMPS = 0;

            fprintf(stdout, "\niter %d \n", iter++);
            for (int t = minMPS; t <= maxMPS; t += passoMPS) {
                vetorAux = vetor;
                estat.resetEstatisticas();

                ordenadorUniversal(vetorAux, t, estat, vetor.tamanho() / 2);
                custos.push_back(estat.calcularCusto());
                imprimeEstatisticas("0", t, custos, numMPS, estat);

                numMPS++;
                vetorMPS.push_back(t);
            }

            for (int i = 0; i < custos.tamanho(); i++) {
                if (custos[i] <= custos[limParticao]) {
                    limParticao = i;
                }
            }

            calculaNovaFaixa(vetorMPS, custos, limParticao, minMPS, maxMPS, passoMPS, numMPS, diffCusto);
            fprintf(stdout, "nummps %d limParticao %d mpsdiff %.6f \n", numMPS, vetorMPS[limParticao], diffCusto);
        } catch (...) {
            fprintf(stderr, "Erro em determinaLimiarParticao.\n");
            break;
        }
    } while ((diffCusto > limiarCusto) and (numMPS >= 5));

    return vetorMPS[limParticao];
}

// Implementado similarmente ao 'determinaLimiarParticao', o método é necessário para definir o 'limQuebras'.
// A diferença está no fato de que este método utiliza do 'minTamParticao' e depende dele para funcionar corretamente.
// Aqui, chamamos os sorts individualmente ao invés de invocar 'ordenadorUniversal', porque queremos comparar os custos entre sorts no mesmo vector.
// Calculando as diferenças entre os custos, obtemos o 'vetorResultante' e o index que guarda o elemento de menor valor é a chave que precisamos.
// Por fim, após aplicar o mesmo processo de refinamento das faixas, obtemos o 'limQuebras', o valor ideal para decidir qual sort será utilizado.
template<typename T>
int ordenadoruniversal<T>::determinaLimiarQuebras(vector<T>& vetor, double limiarCusto, estatisticas& estat, int minTamParticao, int seed) {
    int minQuebras = 1;
    int maxQuebras = (vetor.tamanho()) / 2;
    int passoQuebras = (maxQuebras - minQuebras) / 5;
    if (!(passoQuebras)) {
        passoQuebras++;
    }
    int numTeste = 0;

    int limQuebras = 0;
    float lqdiff = 1e7;
    int iter = 0;

    vector<double> custosQuick;
    vector<double> custosIns;
    //vector<double> custosMerge;
    vector<T> vetorAuxQuick = vetor;
    vector<T> vetorAuxIns;
    //vector<T> vetorAuxMerge;
    vector<int> vetorTQ;

    quickSort(vetorAuxQuick, 0, vetorAuxQuick.tamanho() - 1, estat, minTamParticao);


    do {
        try {
	        custosQuick.limpar();
            custosIns.limpar();
            //custosMerge.limpar();
            vetorTQ.limpar();
            numTeste = 0;

            fprintf(stdout, "\niter %d \n", iter++);
            for (int t = minQuebras; t <= maxQuebras; t += passoQuebras) {
                shuffleVector(vetorAuxQuick, t, seed);
                vetorAuxIns = vetorAuxQuick;
                //vetorAuxMerge = vetorAuxQuick;

                estat.resetEstatisticas();
                quickSort(vetorAuxQuick, 0, vetorAuxQuick.tamanho() - 1, estat, minTamParticao);
                custosQuick.push_back(estat.calcularCusto());
                imprimeEstatisticas("qs", t, custosQuick, numTeste, estat);

                estat.resetEstatisticas();
                insertionSort(vetorAuxIns, 0, vetorAuxIns.tamanho() - 1, estat);
                custosIns.push_back(estat.calcularCusto());
                imprimeEstatisticas("in", t, custosIns, numTeste, estat);

                /*estat.resetEstatisticas();
		        mergeSort(vetorAuxMerge, 0, vetorAuxMerge.tamanho() - 1, estat);
		        custosMerge.push_back(estat.calcularCusto());
		        imprimeEstatisticas("ms", t, custosIns, numTeste, estat);*/

                numTeste++;
                vetorTQ.push_back(t);
            }

            vector<double> vetorResultante;
            for (int i = 0; i < custosQuick.tamanho(); i++) {
                vetorResultante.push_back(std::fabs(custosQuick[i] - custosIns[i]/* - custosMerge[i]*/));
            }

            for (int i = 0; i < custosIns.tamanho(); i++) {
                if (vetorResultante[i] <= vetorResultante[limQuebras]) {
                    limQuebras = i;
                }
            }

            calculaNovaFaixa(vetorTQ, custosIns, limQuebras, minQuebras, maxQuebras, passoQuebras, numTeste, lqdiff);
            fprintf(stdout, "numlq %d limQuebras %d lqdiff %.6f\n", numTeste, vetorTQ[limQuebras], lqdiff);
        } catch (...) {
            fprintf(stderr, "Erro em determinaLimiarQuebras.\n");
            break;
        }
    } while ((lqdiff > limiarCusto) and (numTeste >= 5));

    return vetorTQ[limQuebras];
}

// Método auxiliar de simples implementação que percorre o vector desordenado e conta o número de quebras.
template<typename T>
int ordenadoruniversal<T>::numeroQuebras(vector<T>& vetor) {
    int contador = 0;
    for (int i = 1; i < vetor.tamanho(); ++i) {
        if (vetor[i-1] > vetor[i])
            ++contador;
    }

    return contador;
}

// Método auxiliar para facilitar os prints durante a execução do programa.
// Testa a string, porque a saída é distinta entre o 'determinaLimiarParticao' e 'determinaLimiarQuebras'.
template<typename T>
void ordenadoruniversal<T>::imprimeEstatisticas(std::string sort, int t, vector<double>& custos, int numX, estatisticas& estat) {
    if (sort == "0") {
	    fprintf(stdout, "mps %d cost %.9f cmp %d move %d calls %d \n", t, custos[numX], estat.getComparacoes(), estat.getMovimentacoes(), estat.getChamadas());
    } else {
        fprintf(stdout, "%s lq %d cost %.9f cmp %d move %d calls %d \n", sort.c_str(), t, custos[numX], estat.getComparacoes(), estat.getMovimentacoes(), estat.getChamadas());
    }
}

#endif
