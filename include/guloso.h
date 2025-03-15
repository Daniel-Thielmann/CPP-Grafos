#ifndef GULOSO_H
#define GULOSO_H

#include "grafo_matriz.h"
#include "grafo_lista.h"
#include <iostream>

using namespace std;

class Guloso {
private:
    int* melhorRota;   // Melhor rota encontrada (Agora um array dinâmico)
    int menorCusto;    // Menor custo encontrado
    int numCidades;    // Número de cidades
    int melhorRotaIndex; // Índice para rastrear a melhor rota


    // Definindo manualmente o valor máximo para um int
    static const int INT_MAX = 2147483647;

public:
    Guloso() : melhorRota(nullptr), menorCusto(INT_MAX), numCidades(0), melhorRotaIndex(0) {}

    ~Guloso() {
        delete[] melhorRota;  // Libera a memória alocada dinamicamente
    }

    void resolverTSPMatriz(const GrafoMatriz& grafo);
    
    void resolverTSPLista(const GrafoLista& grafo);
    
    int* getMelhorRota(int& tamanho) const;
    int getMenorCusto() const;
    int getNumCidades() const;
};

#endif