#ifndef LISTA_ADJ_H
#define LISTA_ADJ_H

#include <iostream>

struct NoAdj {
    int destino;
    int peso;
    NoAdj* prox;

    NoAdj(int d, int p) : destino(d), peso(p), prox(nullptr) {}
};

class ListaAdj {
private:
    NoAdj** lista; // Vetor de ponteiros para listas encadeadas
    int numVertices;

public:
    ListaAdj();  // ✅ Construtor padrão
    ListaAdj(int numVertices);
    ~ListaAdj();
    void inserirAresta(int origem, int destino, int peso);
    void imprimir() const;
    std::pair<int, int>* obterVizinhos(int vertice, int& tamanho) const;
};

#endif // LISTA_ADJ_H