#include "grafo_randomizado.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

GrafoRandomizado::GrafoRandomizado(const Grafo& g)
    : grafo(g), melhorRota(nullptr), menorCusto(INT_MAX), numCidades(g.getNumVertices()) {
    if (numCidades <= 0) {
        cerr << "[ERRO] Numero invalido de cidades!" << endl;
    }
}

void GrafoRandomizado::resolver(int iteracoes) {
    if (iteracoes <= 0) {
        cerr << "[ERRO] O numero de iteracoes deve ser positivo!" << endl;
        return;
    }

    if (numCidades <= 1) {
        cerr << "[ERRO] O grafo deve ter pelo menos 2 cidades para calcular um caminho!" << endl;
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

        // 🚀 Embaralhar o vetor de cidades (evita múltiplos swaps)
        for (int j = numCidades - 1; j > 0; j--) {
            int k = rand() % (j + 1);
            swap(cidades[j], cidades[k]);
        }

        int custoAtual = 0;
        bool rotaValida = true;

        for (int j = 0; j < numCidades - 1; j++) {
            int distancia = grafo.obterDistancia(cidades[j], cidades[j + 1]);
            if (distancia <= 0 || distancia >= INT_MAX) { // 🚨 Distâncias inválidas
                rotaValida = false;
                break;
            }
            custoAtual += distancia;
        }

        // 🚀 Fechar o ciclo e verificar a distância de volta à cidade inicial
        int distanciaRetorno = grafo.obterDistancia(cidades[numCidades - 1], cidades[0]);
        if (distanciaRetorno <= 0 || distanciaRetorno >= INT_MAX) {
            rotaValida = false;
        } else {
            custoAtual += distanciaRetorno;
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

    if (menorCusto == INT_MAX) {
        cerr << "[ERRO] Nenhuma solução válida foi encontrada!" << endl;
        menorCusto = -1; // 🚨 Evita que retorne um valor absurdo
    }
}

void GrafoRandomizado::exibirMelhorRota() const {
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

GrafoRandomizado::~GrafoRandomizado() {
    if (melhorRota) {
        delete[] melhorRota;
    }
}

int GrafoRandomizado::getMenorCusto() const {
    return (menorCusto == -1) ? INT_MAX : menorCusto;
}
