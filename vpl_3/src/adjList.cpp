#include "adjList.hpp"
#include <cstddef>

AdjList::AdjList(int n) : numVertices(n), numEdges(0) {
    adjacency = new LinkedList[n];
}

AdjList::~AdjList() {
    delete[] adjacency;
}

void AdjList::addEdge(int v, int w) {
    adjacency[v].addNodeAtEnd(w);  // Usar addNodeAtEnd para preservar a ordem de inserção original
    numEdges++;
}

LinkedList* AdjList::neighbors(int v) const {
    return &adjacency[v];
}

int AdjList::degree(int v) const {
    return adjacency[v].size();
}

int AdjList::vertexCount() const {
    return numVertices;
}

int AdjList::edgeCount() const {
    return numEdges / 2;
}