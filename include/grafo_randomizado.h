#ifndef GRAFORANDOMIZADO_H
#define GRAFORANDOMIZADO_H

#include "Grafo.h"

class GrafoRandomizado {
private:
    const Grafo& grafo;
    int* melhorRota;
    int menorCusto;
    int numCidades;

public:
    GrafoRandomizado(const Grafo& g);
    ~GrafoRandomizado();
    void resolver(int iteracoes);
    void exibirMelhorRota() const;
    int getMenorCusto() const;
};

#endif // GRAFORANDOMIZADO_H
