#ifndef ALGORITMO_RANDOMIZADO_H
#define ALGORITMO_RANDOMIZADO_H

#include "grafo_matriz.h"

class AlgoritmoRandomizado {
private:
    const GrafoMatriz& grafo; // Referência para o grafo
    int menorCusto;           // Menor custo encontrado
    int numCidades;           // Número de cidades no grafo
    int* melhorRota;          // Melhor rota encontrada

public:
    AlgoritmoRandomizado(const GrafoMatriz& g);
    ~AlgoritmoRandomizado();

    void resolver(int iteracoes);
    void exibirMelhorRota() const;

    int obterDistancia(int cidade1, int cidade2) const;
    int obterNumCidades() const;
};

#endif // ALGORITMO_RANDOMIZADO_H
