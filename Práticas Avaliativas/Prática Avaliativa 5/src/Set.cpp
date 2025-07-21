#include "Set.hpp"

StringSet::StringSet(int tamanho) {
    tamanhoOriginal = tamanhoTabela = tamanho;
    tamanhoConjunto = 0;

    tabela = new ElementoTabela[tamanhoTabela];
    for (int i = 0; i < tamanhoTabela; i++) {
        tabela[i].vazio = 1;
        tabela[i].retirada = 0;
    }
}

StringSet::~StringSet() {   
    delete[] tabela;
}

void StringSet::Inserir(string s) {
    if (Pertence(s)) {
        return;
    }
    
    //proporção de N/M; .7 é limite seguro para aumentar;
    if (static_cast<float>(tamanhoConjunto / tamanhoTabela) > 0.75) {
        Resize(tamanhoTabela * 2);
    }

    int pos = Hash(s);
    while (!tabela[pos].vazio and !tabela[pos].retirada) {
        //cout << "Inserindo" << endl;
        pos = (pos + 1) % tamanhoTabela;
    }

    tabela[pos].dado = s;
    tabela[pos].vazio = 0;
    tabela[pos].retirada = 0;
    tamanhoConjunto++;
}

void StringSet::Remover(string s) {
    if (!Pertence(s)) {
        //fprintf(stdout, "Nao da pra remover %s, nao esta na tabela", s.c_str());
            return;
    }

    int pos = Hash(s);
    int guard = pos;

    while (!tabela[pos].vazio) {
        if (!tabela[pos].retirada and tabela[pos].dado == s) {
            //cout << "Procurando para remover" << endl;
            tabela[pos].retirada = 1;
            tamanhoConjunto--;
            return;
        }
        pos = (pos + 1) % tamanhoTabela;
        if (pos == guard) {
            break;
        }
    }
}

bool StringSet::Pertence(string s) {
    int pos = Hash(s);
    int guard = pos;

    while (!tabela[pos].vazio) {
        if (!tabela[pos].retirada and tabela[pos].dado == s) {
            return 1;
        }
        //cout << "Procurando se Pertence" << endl;
        pos = (pos + 1) % tamanhoTabela;
        if (pos == guard) {
            break;
        }
    }

    return 0;
}

StringSet* StringSet::Intersecao(StringSet* S) {
    StringSet* intersec = new StringSet(tamanhoConjunto);

    for (int i = 0; i < tamanhoTabela; i++) {
        if (!tabela[i].vazio and !tabela[i].retirada and S->Pertence(tabela[i].dado)) {
            intersec->Inserir(tabela[i].dado);
        }
    }

    return intersec;
}

StringSet* StringSet::Uniao(StringSet* S) {
    StringSet* unio = new StringSet(S->tamanhoConjunto + tamanhoConjunto);

    for (int i = 0; i < tamanhoTabela; i++) {
        if (!tabela[i].vazio and !tabela[i].retirada) {
            unio->Inserir(tabela[i].dado);
        }
    }
    
    for (int i = 0; i < S->tamanhoTabela; i++) {
        if (!S->tabela[i].vazio and !S->tabela[i].retirada) {
            unio->Inserir(S->tabela[i].dado);
        }
    }

    return unio;
}

StringSet* StringSet::DiferencaSimetrica(StringSet* S) {
    StringSet* simdiff = new StringSet(S->tamanhoConjunto + tamanhoConjunto);

    for (int i = 0; i < tamanhoTabela; i++) {
        if (!tabela[i].vazio and !tabela[i].retirada and !S->Pertence(tabela[i].dado)) {
            cout << i << " iteracao loop 1" << endl;
            simdiff->Inserir(tabela[i].dado);
            cout << "Inserido 1" << endl;
        }
    }

    cout << "Parte 1 concluída" << endl;

    for (int i = 0; i < S->tamanhoTabela; i++) {
        if (!S->tabela[i].vazio and !S->tabela[i].retirada and !Pertence(S->tabela[i].dado)) {
            cout << i << " iteracao loop 2" << endl;
            simdiff->Inserir(S->tabela[i].dado);
            cout << "Inserido 2" << endl;
        }
    }

    cout << "Parte 2 conluída" << endl;

    return simdiff;
}

void StringSet::Imprimir() {
    cout << "{ ";
    short first = 1;
    for (int i = 0; i < tamanhoTabela; i++) {
        if (!tabela[i].vazio and !tabela[i].retirada) {
            if (!first) {
                cout << ", ";
            }
            cout << tabela[i].dado;
            first = 0;
        }
    }
    cout << " }" << endl;
}

int StringSet::Hash(string s) {
    int hash = 0;
    
    for (int i = 0; i < s.size(); i++) {
        hash += (s[i] * (i + 1));
    }

    return hash % tamanhoTabela;
}

void StringSet::Rehash(int pos) {
    return;
}

void StringSet::Resize(size_t tamanho) {
    ElementoTabela* old = tabela;
    int oldsz = tamanhoTabela;

    tabela = new ElementoTabela[tamanho];
    tamanhoTabela = tamanho;
    tamanhoConjunto = 0;

    for (int i = 0; i < tamanho; i++) {
        tabela[i].vazio = 1;
        tabela[i].retirada = 0;
    }

    for (int i = 0; i < oldsz; i++) {
        if (!old[i].vazio and !old[i].retirada) {
            Inserir(old[i].dado);
        }   
    }

    delete[] old;
}
