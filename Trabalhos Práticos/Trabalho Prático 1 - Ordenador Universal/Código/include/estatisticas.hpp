#ifndef ESTATISTICAS_HPP
#define ESTATISTICAS_HPP

// Classe para registrar as estatísticas de cada sort feito.
// Todas os métodos, com exceção do construtor e de calcularCusto(), são internas e restritas aos atributos da classe, portanto, foram definidas como void.
class estatisticas {
private:
    double a;
    double b;
    double c;
    int comparacoes;
    int movimentacoes;
    int chamadas;

public:
    // a,b,c são parâmetros externos ao código, portanto devem ser inseridos pelo construtor.
    estatisticas(double _a, double _b, double _c);

    // Métodos getters dos atributos.
    int getComparacoes();
    int getMovimentacoes();
    int getChamadas();

    // Método para zerar os atributos (comparações, movimentações e chamadas), permitindo o reuso da instância da classe.
    void resetEstatisticas();

    // Método que será necessária no TAD OrdenadorUniversal, responsável pelo cálculo do custo de cada sub-iteração do programa.
    double calcularCusto();    

    //MÉTODOS DE INCREMENTO DE VALOR DAS VARIÁVEIS    

    // Comparações   
    void incComparacoes();
    void incComparacoes(int num);

    // Movimentações
    void incMovimentacoes();
    void incMovimentacoes(int num);

    // Chamadas
    void incChamadas();
    void incChamadas(int num);

};

#endif