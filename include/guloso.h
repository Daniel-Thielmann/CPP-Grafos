#ifndef GULOSO_H
#define GULOSO_H

#include "grafo_matriz.h"
#include "grafo_lista.h"
#include <iostream>

using namespace std;

class Guloso {
private:
    int* melhorRota;   // Melhor rota encontrada (array dinâmico)
    int menorCusto;    // Menor custo encontrado
    int numCidades;    // Número de cidades
    int melhorRotaIndex; // Índice para rastrear a melhor rota

    static const int MAX_INT = 2147483647; // Define manualmente o valor máximo para um int

public:
    Guloso() : melhorRota(nullptr), menorCusto(MAX_INT), numCidades(0), melhorRotaIndex(0) {}

    ~Guloso() {
        if (melhorRota) {
            delete[] melhorRota;
        }
    }

    void resolverTSPMatriz(const GrafoMatriz& grafo);
    void resolverTSPLista(const GrafoLista& grafo);

    int* getMelhorRota(int& tamanho) const;
    int getMenorCusto() const;
    int getNumCidades() const;
};

#endif // GULOSO_H
