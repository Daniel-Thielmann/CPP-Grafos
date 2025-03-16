#ifndef GRAFORANDOMIZADO_H
#define GRAFORANDOMIZADO_H

#include "Grafo.h"

// Classe que implementa um algoritmo randomizado para o problema do Caixeiro Viajante
class GrafoRandomizado {
private:
    const Grafo& grafo; // Referência para o grafo
    int* melhorRota;    // Armazena a melhor rota encontrada (array dinâmico)
    int menorCusto;     // Armazena o menor custo encontrado
    int numCidades;     // Armazena o número de cidades no grafo

public:
    GrafoRandomizado(const Grafo& g);  // Construtor
    ~GrafoRandomizado();               // Destrutor para liberar memória alocada
    void resolver(int iteracoes);      // Executa a busca aleatória para encontrar a melhor rota
    void exibirMelhorRota() const;     // Exibe a melhor rota encontrada e seu custo
};

#endif