#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

Heap* NovoHeap(int maxsize) {
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->tamanho = 0;
    h->dados = (int*)malloc(maxsize * sizeof(int));
    return h;
}

void DeletaHeap(Heap* h) {
    free(h->dados);
    free(h);
}

int GetAncestral(Heap* h, int posicao) {
    (void)h;
    return (posicao - 1) / 2;
}

int GetSucessorEsq(Heap* h, int posicao) {
    (void)h;
    return 2 * posicao + 1;
}

int GetSucessorDir(Heap* h, int posicao) {
    (void)h;
    return 2 * posicao + 2;
}

void HeapifyPorBaixo(Heap* h, int posicao) {
    int menor = posicao;
    int esq = GetSucessorEsq(h, posicao);
    int dir = GetSucessorDir(h, posicao);

    if (esq < h->tamanho && h->dados[esq] < h->dados[menor])
        menor = esq;

    if (dir < h->tamanho && h->dados[dir] < h->dados[menor])
        menor = dir;

    if (menor != posicao) {
        int temp = h->dados[posicao];
        h->dados[posicao] = h->dados[menor];
        h->dados[menor] = temp;
        HeapifyPorBaixo(h, menor);
    }
}

void HeapifyPorCima(Heap* h, int posicao) {
    int ancestral = GetAncestral(h, posicao);
    while (posicao > 0 && h->dados[ancestral] > h->dados[posicao]) {
        int temp = h->dados[posicao];
        h->dados[posicao] = h->dados[ancestral];
        h->dados[ancestral] = temp;
        posicao = ancestral;
        ancestral = GetAncestral(h, posicao);
    }
}

void Inserir(Heap* h, int x) {
    h->dados[h->tamanho] = x;
    h->tamanho++;
    HeapifyPorCima(h, h->tamanho - 1);
}

int Remover(Heap* h) {
    if (Vazio(h)) return -1;

    int raiz = h->dados[0];
    h->dados[0] = h->dados[h->tamanho - 1];
    h->tamanho--;
    HeapifyPorBaixo(h, 0);

    return raiz;
}

int Vazio(Heap* h) {
    return h->tamanho == 0;
}