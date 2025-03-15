#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

#include "grafo.h"

class GrafoMatriz : public Grafo {
private:
    int** matrizAdj; // Matriz dinâmica para reduzir uso de memória
    int numVertices;

public:
    GrafoMatriz(int numVertices, bool direcionado, bool verticesPonderados, bool arestasPonderadas);
    ~GrafoMatriz();

    void adicionarAresta(int origem, int destino, int peso) override;
    void imprimirGrafo() const override;
    void carregarGrafo(const std::string& nomeArquivo) override;
    std::pair<int, int>* getArestas(int vertice, int& tamanho) const override;
    int getPesoAresta(int origem, int destino) const;
};

#endif // GRAFO_MATRIZ_H
