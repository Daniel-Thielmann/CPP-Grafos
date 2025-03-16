#ifndef AlgoritmoRandomizado_H
#define AlgoritmoRandomizado_H

#include "Grafo.h"
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
    ~AlgoritmoRandomizado();               // Destrutor para liberar memória alocada
    void resolver(double iteracoes);      // Executa a busca aleatória para encontrar a melhor rota
    void exibirMelhorRota() const;     // Exibe a melhor rota encontrada e seu custo

    int obterDistancia(int cidade1, int cidade2) const;
    int obterNumCidades() const;
};

#endif

/*#ifndef ALGORITMO_RANDOMIZADO_H
#define ALGORITMO_RANDOMIZADO_H

#include "grafo_matriz.h" // Inclua o arquivo de cabeçalho do grafo

class AlgoritmoRandomizado {
private:
    const GrafoMatriz& grafo; // Referência para o grafo
    int menorCusto;           // Menor custo encontrado
    int numCidades;           // Número de cidades
    int* melhorRota;          // Melhor rota encontrada

public:
    // Construtor
    AlgoritmoRandomizado(const GrafoMatriz& g);

    // Destrutor
    ~AlgoritmoRandomizado();

    // Método para resolver o problema do caixeiro viajante
    void resolver();

    // Método para exibir a melhor rota encontrada
    void exibirMelhorRota() const;

    // Método para obter a distância entre duas cidades
    int obterDistancia(int cidade1, int cidade2) const;

    // Método para obter o número de cidades
    int obterNumCidades() const;
};

#endif // ALGORITMO_RANDOMIZADO_H*/
