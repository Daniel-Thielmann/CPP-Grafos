#include "grafo_randomizado.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

// ✅ ORDEM DE INICIALIZAÇÃO CORRIGIDA!
GrafoRandomizado::GrafoRandomizado(const Grafo& g)
    : grafo(g), melhorRota(nullptr), menorCusto(INT_MAX), numCidades(g.getNumVertices()) {}

void GrafoRandomizado::resolver(int iteracoes) {
    if (iteracoes <= 0) {
        cerr << "[ERRO] O numero de iteracoes deve ser positivo!" << endl;
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

void GrafoRandomizado::exibirMelhorRota() const {
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

GrafoRandomizado::~GrafoRandomizado() {
    if (melhorRota) {
        delete[] melhorRota;
    }
}
