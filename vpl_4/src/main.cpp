#include <iostream>
#include "unionFind.hpp"

using namespace std;

// Função para comparar as arestas pelo custo
void ordenarArestas(Aresta arestas[], int m) {
    for (int i = 0; i < m - 1; ++i) {
        for (int j = 0; j < m - i - 1; ++j) {
            if (arestas[j].custo > arestas[j + 1].custo) {
                Aresta temp = arestas[j];
                arestas[j] = arestas[j + 1];
                arestas[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    Aresta* arestas = new Aresta[m];
    for (int i = 0; i < m; ++i) {
        cin >> arestas[i].u >> arestas[i].v >> arestas[i].custo;
    }

    // Ordena as arestas pelo custo
    ordenarArestas(arestas, m);

    UnionFind dsu(n);
    int custoTotal = 0;
    int arestasUsadas = 0;

    for (int i = 0; i < m; ++i) {
        int u = arestas[i].u;
        int v = arestas[i].v;
        int custo = arestas[i].custo;

        if (dsu.Find(u) != dsu.Find(v)) {
            dsu.Union(u, v);
            custoTotal += custo;
            arestasUsadas++;
        }

        // Se arestas = n - 1, então árvore completa
        if (arestasUsadas == n - 1) {
            break;
        }
    }

    cout << custoTotal << endl;

    delete[] arestas;
    return 0;
}