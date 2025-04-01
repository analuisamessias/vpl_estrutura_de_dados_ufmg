#include "grafo.hpp"
#include <iostream>

Grafo::Grafo(int n) : vertices(n) {}

Grafo::~Grafo() {}

void Grafo::InsereVertice() {
    // Aqui, a inserção de vértices poderia ser dinâmica.
}

void Grafo::InsereAresta(int v, int w) {
    vertices.addEdge(v, w);
}

int Grafo::QuantidadeVertices() {
    return vertices.vertexCount();
}

int Grafo::QuantidadeArestas() {
    return vertices.edgeCount();
}

int Grafo::GrauMinimo() {
    int minDegree = vertices.degree(0);
    for (int i = 1; i < vertices.vertexCount(); ++i) {
        int degree = vertices.degree(i);
        if (degree < minDegree) {
            minDegree = degree;
        }
    }
    return minDegree;
}

int Grafo::GrauMaximo() {
    int maxDegree = vertices.degree(0);
    for (int i = 1; i < vertices.vertexCount(); ++i) {
        int degree = vertices.degree(i);
        if (degree > maxDegree) {
            maxDegree = degree;
        }
    }
    return maxDegree;
}

void Grafo::ImprimeVizinhos(int v) {
    Node* neighbor = vertices.neighbors(v)->begin();
    while (neighbor != NULL) {
        std::cout << neighbor->value << " ";
        neighbor = neighbor->next;
    }
    std::cout << std::endl;
}

bool Grafo::EhCompleto() {
    int n = vertices.vertexCount();
    int totalEdges = n * (n - 1) / 2;
    return vertices.edgeCount() == totalEdges;
}