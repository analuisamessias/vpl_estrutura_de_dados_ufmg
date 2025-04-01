#include <iostream>
#include "set.hpp"

StringSet::StringSet(int tamanho) {
    this->tamanhoOriginal = tamanho;
    this->tamanhoTabela = tamanho;
    this->tamanhoConjunto = 0;
    this->tabela = new ElementoTabela[tamanho];

    for (int i = 0; i < tamanho; i++) {
        this->tabela[i].vazio = true;
        this->tabela[i].retirada = false;
    }
}

StringSet::~StringSet() {
    delete[] tabela;
}

void StringSet::Resize(size_t tamanho) {
    ElementoTabela* novaTabela = new ElementoTabela[tamanho];

    for (size_t i = 0; i < tamanho; i++) {
        novaTabela[i].vazio = true;
    }

    for (int i = 0; i < this->tamanhoTabela; i++) {
        if (!this->tabela[i].vazio && !this->tabela[i].retirada) {
            int novaPos = Hash(this->tabela[i].dado) % tamanho;
            while (!novaTabela[novaPos].vazio) {
                novaPos = (novaPos + 1) % tamanho;
            }
            novaTabela[novaPos] = this->tabela[i];
        }
    }

    delete[] tabela;
    this->tabela = novaTabela;
    this->tamanhoTabela = tamanho;
}

void StringSet::Inserir(string s) {
    if (Pertence(s)) {
        return;
    }

    if (this->tamanhoConjunto >= this->tamanhoTabela / 2) {
        Resize(this->tamanhoTabela * 2);
    }

    int pos = Hash(s);
    while (!this->tabela[pos].vazio) {
        pos = (pos + 1) % this->tamanhoTabela;
    }

    this->tabela[pos].dado = s;
    this->tabela[pos].vazio = false;
    this->tabela[pos].retirada = false;
    this->tamanhoConjunto++;
}

void StringSet::Remover(string s) {
    int pos = Hash(s);

    while (!this->tabela[pos].vazio) {
        if (this->tabela[pos].dado == s && !this->tabela[pos].retirada) {
            this->tabela[pos].retirada = true;
            this->tamanhoConjunto--;
            return;
        }
        pos = (pos + 1) % this->tamanhoTabela;
    }
}

bool StringSet::Pertence(string s) {
    int pos = Hash(s);

    while (!this->tabela[pos].vazio) {
        if (this->tabela[pos].dado == s && !this->tabela[pos].retirada) {
            return true;
        }
        pos = (pos + 1) % this->tamanhoTabela;
    }

    return false;
}

StringSet* StringSet::Intersecao(StringSet* S) {
    StringSet* intersecao = new StringSet(this->tamanhoTabela);

    for (int i = 0; i < this->tamanhoTabela; i++) {
        if (!this->tabela[i].vazio && !this->tabela[i].retirada && S->Pertence(this->tabela[i].dado)) {
            intersecao->Inserir(this->tabela[i].dado);
        }
    }

    return intersecao;
}

StringSet* StringSet::Uniao(StringSet* S) {
    StringSet* uniao = new StringSet(this->tamanhoTabela + S->tamanhoTabela);

    for (int i = 0; i < this->tamanhoTabela; i++) {
        if (!this->tabela[i].vazio && !this->tabela[i].retirada) {
            uniao->Inserir(this->tabela[i].dado);
        }
    }

    for (int i = 0; i < S->tamanhoTabela; i++) {
        if (!S->tabela[i].vazio && !S->tabela[i].retirada) {
            uniao->Inserir(S->tabela[i].dado);
        }
    }

    return uniao;
}

StringSet* StringSet::DiferencaSimetrica(StringSet* S) {
    StringSet* diferenca = Uniao(S);

    for (int i = 0; i < this->tamanhoTabela; i++) {
        if (!this->tabela[i].vazio && !this->tabela[i].retirada && S->Pertence(this->tabela[i].dado)) {
            diferenca->Remover(this->tabela[i].dado);
        }
    }

    for (int i = 0; i < S->tamanhoTabela; i++) {
        if (!S->tabela[i].vazio && !S->tabela[i].retirada && this->Pertence(S->tabela[i].dado)) {
            diferenca->Remover(S->tabela[i].dado);
        }
    }

    return diferenca;
}

void StringSet::Imprimir() {
    cout << "{ ";
    bool primeiro = true;

    for (int i = 0; i < this->tamanhoTabela; i++) {
        if (!this->tabela[i].vazio && !this->tabela[i].retirada) {
            if (!primeiro) {
                cout << ", ";
            }
            cout << this->tabela[i].dado;
            primeiro = false;
        }
    }

    cout << " }" << endl;
}

int StringSet::Hash(string s) {
    int hash = 0;
    for (char c : s) {
        hash = (hash * 31 + c) % this->tamanhoTabela;
    }
    return hash;
}