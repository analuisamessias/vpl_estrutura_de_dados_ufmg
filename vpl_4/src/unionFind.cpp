#include "unionFind.hpp"

UnionFind::UnionFind(int quantidade_subconjuntos) {
    tamanho = quantidade_subconjuntos;
    subconjuntos = new Subconjunto[quantidade_subconjuntos];
    for (int i = 0; i < quantidade_subconjuntos; ++i) {
        subconjuntos[i].representante = i;
        subconjuntos[i].rank = 0;
    }
}

UnionFind::~UnionFind() {
    delete[] subconjuntos;
}

int UnionFind::Find(int x) {
    if (subconjuntos[x].representante != x) {
        subconjuntos[x].representante = Find(subconjuntos[x].representante); // Path compression
    }
    return subconjuntos[x].representante;
}

void UnionFind::Union(int x, int y) {
    int raizX = Find(x);
    int raizY = Find(y);

    if (raizX != raizY) {
        if (subconjuntos[raizX].rank < subconjuntos[raizY].rank) {
            subconjuntos[raizX].representante = raizY;
        } else if (subconjuntos[raizX].rank > subconjuntos[raizY].rank) {
            subconjuntos[raizY].representante = raizX;
        } else {
            subconjuntos[raizY].representante = raizX;
            subconjuntos[raizX].rank++;
        }
    }
}