#ifndef GRAFO_HPP
#define GRAFO_HPP

#include "adjList.hpp"

class Grafo {
public:
    Grafo(int n);
    ~Grafo();
    void InsereVertice();
    void InsereAresta(int v, int w);
    int QuantidadeVertices();
    int QuantidadeArestas();
    int GrauMinimo();
    int GrauMaximo();
    void ImprimeVizinhos(int v);
    bool EhCompleto();

private:
    AdjList vertices;
};

#endif // GRAFO_HPP