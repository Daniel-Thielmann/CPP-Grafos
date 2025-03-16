#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

#include "grafo.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>  // Para memset

class GrafoMatriz : public Grafo {
private:
    int* matrizAdj;   // Matriz compacta em array unidimensional
    bool* cacheArestas; // Bitmap para verificar se uma aresta existe sem acessar diretamente a matriz
    int numVertices;

public:
    GrafoMatriz(int numVertices, bool direcionado, bool verticesPonderados, bool arestasPonderadas);
    ~GrafoMatriz();

    void adicionarAresta(int origem, int destino, int peso) override;
    void imprimirGrafo() const override;
    void carregarGrafo(const std::string& nomeArquivo) override;
    std::pair<int, int>* getArestas(int vertice, int& tamanho) const override;
    int getPesoAresta(int origem, int destino) const;
    int obterDistancia(int cidade1, int cidade2) const override;
    int obterNumCidades() const;
};

#endif // GRAFO_MATRIZ_H
