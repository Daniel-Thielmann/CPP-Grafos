#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

#include "grafo.h"

class GrafoMatriz : public Grafo {
private:
    vector<vector<int>> matrizAdj;

public:
    GrafoMatriz(int numVertices, bool direcionado, bool verticesPonderados, bool arestasPonderadas);
    ~GrafoMatriz() {}

    void adicionarAresta(int origem, int destino, int peso) override;
    void imprimirGrafo() const override;
    void carregarGrafo(const string& nomeArquivo) override;
    pair<int, int>* getArestas(int vertice, int& tamanho) const override;
    
};

#endif // GRAFO_MATRIZ_H