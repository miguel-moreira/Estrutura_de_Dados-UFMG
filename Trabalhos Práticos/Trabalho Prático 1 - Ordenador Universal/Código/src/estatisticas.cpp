// Código de implementação dos metódos definidas no header 'estatisticas.hpp'.
#include "estatisticas.hpp"

// Construtor da classe, comparações, movimentações e chamadas são 0, porque nada foi registrado inicialmente. 
// Já os outros atributos são recebidos na main.
estatisticas::estatisticas(double _a, double _b, double _c) {
    this->a = _a;
    this->b = _b;
    this->c = _c;
    this->comparacoes = this->movimentacoes = this->chamadas = 0;
}

// Métodos 'getters' que retornam atributos da classe. 
// Comparações, movimentações e chamadas, respectivamente.
int estatisticas::getComparacoes() {
    return this->comparacoes;
}
int estatisticas::getMovimentacoes() {
    return this->movimentacoes;
}
int estatisticas::getChamadas() {
    return this->chamadas;
}

//função responsável por zerar as estatísticas que variam durante a execução do programa, comparações, movimentações e chamadas, permitindo reuso da mesma instância repetidas vezes.
void estatisticas::resetEstatisticas() {
    this->comparacoes = this->movimentacoes = this->chamadas = 0;
}

//função dada no enunciado do Trabalho Prático, definida como o modo de definir o custo de cada iteração empiricamente.
double estatisticas::calcularCusto() {
    return a*comparacoes + b*movimentacoes + c*chamadas;
}

//MÉTODOS DE INCREMENTO
// Estes métodos são os responsáveis por registrar as estatísticas e recebendo um parâmetro inteiro, somam este ao valor do atributo.
// Caso não receba valor, soma 1 ao atributo. Serão usados dentro dos sorts.

//Comparações
void estatisticas::incComparacoes() {
    this->comparacoes++;
}
void estatisticas::incComparacoes(int num) {
    this->comparacoes += num;
}

// Movimentações
void estatisticas::incMovimentacoes() {
    this->movimentacoes++;
}
void estatisticas::incMovimentacoes(int num) {
    this->movimentacoes += num;
}

// Chamadas
void estatisticas::incChamadas() {
    this->chamadas++;
}
void estatisticas::incChamadas(int num) {
    this->chamadas += num;
}