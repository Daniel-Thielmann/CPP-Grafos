#include "AlgoritmoRandomizado.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

// Construtor: inicializa o objeto e define o menor custo como infinito
AlgoritmoRandomizado::AlgoritmoRandomizado(const GrafoMatriz& g) 
    : grafo(g), menorCusto(INT_MAX), numCidades(g.getNumVertices()), melhorRota(nullptr) {}

void AlgoritmoRandomizado::resolver(int iteracoes) {
    if (iteracoes <= 0) {
        cerr << "[ERRO] O numero de iterações deve ser positivo!" << endl;
        return;
    }

    int* cidades = new int[numCidades];

    for (int i = 0; i < numCidades; i++) {
        cidades[i] = i;
    }

    srand(time(nullptr));

    for (int i = 0; i < iteracoes; i++) {
        if (i % 100 == 0) {
            cout << "[LOG] Iteracao " << i << " de " << iteracoes << "..." << endl;
        }

        for (int j = numCidades - 1; j > 0; j--) {
            int k = rand() % (j + 1);
            swap(cidades[j], cidades[k]);
        }

        int custoAtual = 0;
        for (int j = 0; j < numCidades - 1; j++) {
            custoAtual += grafo.obterDistancia(cidades[j], cidades[j + 1]);
        }
        custoAtual += grafo.obterDistancia(cidades[numCidades - 1], cidades[0]);

        if (custoAtual < menorCusto) {
            menorCusto = custoAtual;

            if (melhorRota) {
                delete[] melhorRota;
            }
            melhorRota = new int[numCidades];

            for (int j = 0; j < numCidades; j++) {
                melhorRota[j] = cidades[j];
            }
        }
    }

    delete[] cidades;
}

void AlgoritmoRandomizado::exibirMelhorRota() const {
    if (!melhorRota) {
        cout << "Nenhuma rota encontrada." << endl;
        return;
    }

    cout << "Melhor rota encontrada: ";
    for (int i = 0; i < numCidades; i++) {
        cout << melhorRota[i] << " -> ";
    }
    cout << melhorRota[0] << endl;
    cout << "Custo: " << menorCusto << endl;
}

// Método para obter a distância entre duas cidades
int AlgoritmoRandomizado::obterDistancia(int cidade1, int cidade2) const {
    if (cidade1 >= 0 && cidade1 < numCidades && cidade2 >= 0 && cidade2 < numCidades) {
        return grafo.obterDistancia(cidade1, cidade2);
    } else {
        cerr << "[ERRO] Índices de cidade inválidos: " << cidade1 << ", " << cidade2 << endl;
        return INT_MAX; // Retorna um valor alto para evitar erros
    }
}

// Método para obter o número de cidades
int AlgoritmoRandomizado::obterNumCidades() const {
    return numCidades;
}

// Destrutor para liberar a memória alocada dinamicamente
AlgoritmoRandomizado::~AlgoritmoRandomizado() {
    delete[] melhorRota;
}
