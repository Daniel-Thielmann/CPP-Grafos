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

    int obterDistancia(int cidade1, int cidade2) const override;
    int obterNumCidades() const;
};

#endif // GRAFO_MATRIZ_H
