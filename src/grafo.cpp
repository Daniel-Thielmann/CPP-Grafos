#include "grafo.h"

// Construtor
Grafo::Grafo(int numVertices, bool direcionado, bool verticesPonderados, bool arestasPonderadas) {
    this->numVertices = numVertices;
    this->direcionado = direcionado;
    this->verticesPonderados = verticesPonderados;
    this->arestasPonderadas = arestasPonderadas;
}

// Métodos auxiliares
int Grafo::getNumVertices() const {
    return numVertices;
}

bool Grafo::ehDirecionado() const {
    return direcionado;
}

bool Grafo::temVerticesPonderados() const {
    return verticesPonderados;
}

bool Grafo::temArestasPonderadas() const {
    return arestasPonderadas;
}

int Grafo::obterNumCidades() const {
    return numVertices;  // Retorna o número total de vértices do grafo
}
