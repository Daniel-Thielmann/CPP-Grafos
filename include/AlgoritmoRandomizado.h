#ifndef ALGORITMO_RANDOMIZADO_H
#define ALGORITMO_RANDOMIZADO_H

#include "grafo_matriz.h"

// Classe que implementa um algoritmo randomizado para o problema do Caixeiro Viajante
class AlgoritmoRandomizado {
private:
    const GrafoMatriz& grafo; // Referência para o grafo
    int menorCusto;     // Armazena o menor custo encontrado
    int numCidades;     // Armazena o número de cidades no grafo
    int* melhorRota;    // Armazena a melhor rota encontrada (array dinâmico)

public:
    AlgoritmoRandomizado(const GrafoMatriz& g);  // Construtor
    ~AlgoritmoRandomizado();                     // Destrutor para liberar memória alocada

    void resolver(int iteracoes);                // Executa a busca aleatória para encontrar a melhor rota
    void exibirMelhorRota() const;               // Exibe a melhor rota encontrada e seu custo

    int obterDistancia(int cidade1, int cidade2) const;
    int obterNumCidades() const;
};

#endif // ALGORITMO_RANDOMIZADO_H
