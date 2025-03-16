#include "Grafo_randomizado.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

// Construtor: inicializa o objeto e define o menor custo como infinito (INT_MAX)
GrafoRandomizado::GrafoRandomizado(const Grafo& g) : grafo(g), menorCusto(INT_MAX) {}

// Método que resolve o problema do caixeiro viajante usando um algoritmo randomizado
void GrafoRandomizado::resolver(int iteracoes) {
    int numCidades = grafo.obterNumCidades();
    int* cidades = new int[numCidades];

    // Preenche o array com todas as cidades disponíveis
    for (int i = 0; i < numCidades; i++) {
        cidades[i] = i;
    }

    // Inicializa a semente do gerador de números aleatórios para garantir diversidade nos testes
    srand(time(nullptr));

    // Executa o algoritmo por um número determinado de iterações
    for (int i = 0; i < iteracoes; i++) {
        // Embaralha aleatoriamente a ordem das cidades para gerar uma nova solução
        for (int j = numCidades - 1; j > 0; j--) {
            int k = rand() % (j + 1);
            swap(cidades[j], cidades[k]);
        }

        // Calcula o custo da rota atual
        int custoAtual = 0;
        for (int j = 0; j < numCidades - 1; j++) {
            custoAtual += grafo.obterDistancia(cidades[j], cidades[j + 1]);
        }
        // Fecha o ciclo voltando para a cidade inicial
        custoAtual += grafo.obterDistancia(cidades[numCidades - 1], cidades[0]);

        // Se o custo encontrado for melhor, atualiza a melhor rota e o menor custo
        if (custoAtual < menorCusto) {
            menorCusto = custoAtual;
            // Copia a rota atual para a melhor rota
            delete[] melhorRota;
            melhorRota = new int[numCidades];
            for (int j = 0; j < numCidades; j++) {
                melhorRota[j] = cidades[j];
            }
        }
    }

    delete[] cidades;
}

// Método que exibe a melhor rota encontrada e seu custo
void GrafoRandomizado::exibirMelhorRota() const {
    cout << "Melhor rota encontrada: ";
    for (int i = 0; i < grafo.obterNumCidades(); i++) {
        cout << melhorRota[i] << " -> ";
    }
    cout << melhorRota[0] << endl; // Fecha o ciclo voltando para a cidade inicial
    cout << "Custo: " << menorCusto << endl;
}

// Destrutor para liberar a memória alocada dinamicamente
GrafoRandomizado::~GrafoRandomizado() {
    delete[] melhorRota;
}
