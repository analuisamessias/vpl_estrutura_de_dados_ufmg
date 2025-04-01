#include "grafo.hpp"
#include <iostream>
#include <cstring>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: ./pa3.out [opção]" << std::endl;
        return 1;
    }

    int n;
    std::cin >> n;
    Grafo grafo(n);

    for (int i = 0; i < n; ++i) {
        int m;
        std::cin >> m;
        for (int j = 0; j < m; ++j) {
            int vizinho;
            std::cin >> vizinho;
            grafo.InsereAresta(i, vizinho);
        }
    }

    if (strcmp(argv[1], "-d") == 0) {
        std::cout << grafo.QuantidadeVertices() << std::endl;
        std::cout << grafo.QuantidadeArestas() << std::endl;
        std::cout << grafo.GrauMinimo() << std::endl;
        std::cout << grafo.GrauMaximo() << std::endl;
    } else if (strcmp(argv[1], "-n") == 0) {
        for (int i = 0; i < grafo.QuantidadeVertices(); ++i) {
            grafo.ImprimeVizinhos(i);
        }
    } else if (strcmp(argv[1], "-k") == 0) {
        std::cout << grafo.EhCompleto() << std::endl;
    } else {
        std::cerr << "Opção inválida." << std::endl;
        return 1;
    }

    return 0;
}