#include "AlgoritmoRandomizado.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

AlgoritmoRandomizado::AlgoritmoRandomizado(const GrafoMatriz& g) 
    : grafo(g), menorCusto(INT_MAX), numCidades(g.getNumVertices()), melhorRota(nullptr) {
    if (numCidades <= 0) {
        cerr << "[ERRO] Número inválido de cidades no grafo!" << endl;
    }
}

void AlgoritmoRandomizado::resolver(int iteracoes) {
    if (iteracoes <= 0) {
        cerr << "[ERRO] O número de iterações deve ser positivo!" << endl;
        return;
    }

    int* cidades = new int[numCidades];

    for (int i = 0; i < numCidades; i++) {
        cidades[i] = i;
    }

    srand(time(nullptr));

    for (int i = 0; i < iteracoes; i++) {
        if (i % 100 == 0) {
            cout << "[LOG] Iteração " << i << " de " << iteracoes << "..." << endl;
        }

        // Embaralha cidades para criar uma nova rota
        for (int j = numCidades - 1; j > 0; j--) {
            int k = rand() % (j + 1);
            swap(cidades[j], cidades[k]);
        }

        int custoAtual = 0;
        bool rotaValida = true;

        for (int j = 0; j < numCidades - 1; j++) {
            int distancia = grafo.obterDistancia(cidades[j], cidades[j + 1]);

            if (distancia == INT_MAX) {
                cout << "[ERRO] Distância inválida entre " << cidades[j] << " e " << cidades[j + 1] << ".\n";
                rotaValida = false;
                break;
            }

            if (custoAtual > INT_MAX - distancia) { // Evita overflow
                cout << "[ERRO] Overflow detectado na soma do custo da rota!\n";
                rotaValida = false;
                break;
            }

            custoAtual += distancia;
        }

        // Adiciona a distância de volta ao ponto inicial
        int distanciaFinal = grafo.obterDistancia(cidades[numCidades - 1], cidades[0]);
        if (distanciaFinal == INT_MAX || custoAtual > INT_MAX - distanciaFinal) {
            cout << "[ERRO] Distância final inválida ou overflow detectado.\n";
            rotaValida = false;
        } else {
            custoAtual += distanciaFinal;
        }

        if (rotaValida && custoAtual < menorCusto) {
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
    if (!melhorRota || menorCusto == -1) {
        cout << "[ERRO] Nenhuma rota foi encontrada." << endl;
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
        int distancia = grafo.obterDistancia(cidade1, cidade2);
        return (distancia >= 0) ? distancia : INT_MAX; // Evita valores negativos
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
