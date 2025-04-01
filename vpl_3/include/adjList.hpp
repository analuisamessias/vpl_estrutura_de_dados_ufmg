#ifndef ADJLIST_HPP
#define ADJLIST_HPP

#include "linkedList.hpp"

class AdjList {
public:
    AdjList(int n);
    ~AdjList();
    void addEdge(int v, int w);
    LinkedList* neighbors(int v) const;
    int degree(int v) const;
    int vertexCount() const;
    int edgeCount() const;

private:
    LinkedList* adjacency;
    int numVertices;
    int numEdges;
};

#endif // ADJLIST_HPP