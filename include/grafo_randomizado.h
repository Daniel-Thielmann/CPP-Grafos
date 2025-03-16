#ifndef GRAFORANDOMIZADO_H
#define GRAFORANDOMIZADO_H

#include "Grafo.h"

// Classe que implementa um algoritmo randomizado para o problema do Caixeiro Viajante
class GrafoRandomizado {
private:
    const Grafo& grafo; // PRIMEIRO: Referência para o grafo
    int* melhorRota;    // SEGUNDO: Melhor rota encontrada (array dinâmico)
    int menorCusto;     // TERCEIRO: Menor custo encontrado
    int numCidades;     // QUARTO: Número de cidades no grafo

public:
    GrafoRandomizado(const Grafo& g);  // Construtor
    ~GrafoRandomizado();               // Destrutor para liberar memória alocada
    void resolver(int iteracoes);      // Executa a busca aleatória para encontrar a melhor rota
    void exibirMelhorRota() const;     // Exibe a melhor rota encontrada e seu custo
};

#endif // GRAFORANDOMIZADO_H
