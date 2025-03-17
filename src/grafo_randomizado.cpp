#include "grafo_randomizado.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

// ✅ Construtor corrigido para garantir valores iniciais válidos
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

    bool encontrouSolucao = false;

    for (int i = 0; i < iteracoes; i++) {
        if (i % 100 == 0) {
            cout << "[LOG] Iteracao " << i << " de " << iteracoes << "..." << endl;
        }

        // ✅ Fisher-Yates Shuffle para gerar permutação válida
        for (int j = numCidades - 1; j > 0; j--) {
            int k = rand() % (j + 1);
            swap(cidades[j], cidades[k]);
        }

        int custoAtual = 0;
        bool caminhoValido = true;

        for (int j = 0; j < numCidades - 1; j++) {
            int distancia = grafo.obterDistancia(cidades[j], cidades[j + 1]);
            if (distancia <= 0) {  // ❌ Evita arestas inválidas
                caminhoValido = false;
                break;
            }
            custoAtual += distancia;
        }

        // ✅ Fecha o ciclo para retornar à cidade inicial
        int distanciaRetorno = grafo.obterDistancia(cidades[numCidades - 1], cidades[0]);
        if (distanciaRetorno <= 0) {
            caminhoValido = false;
        } else {
            custoAtual += distanciaRetorno;
        }

        if (caminhoValido && custoAtual < menorCusto) {
            menorCusto = custoAtual;
            encontrouSolucao = true;

            if (melhorRota) {
                delete[] melhorRota;
            }
            melhorRota = new int[numCidades];
            for (int j = 0; j < numCidades; j++) {
                melhorRota[j] = cidades[j];
            }
        }
    }

    // ✅ Se nenhuma solução foi encontrada, manter `menorCusto` como INT_MAX
    if (!encontrouSolucao) {
        menorCusto = INT_MAX;
        cout << "[ERRO] Nenhuma solução válida foi encontrada!" << endl;
    }

    delete[] cidades;
}

// ✅ Adicionada verificação para evitar imprimir uma rota inválida
void GrafoRandomizado::exibirMelhorRota() const {
    if (!melhorRota || menorCusto == INT_MAX) {
        cout << "[ERRO] Nenhuma rota válida encontrada!" << endl;
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

// ✅ Garante que `menorCusto` só retorna um valor válido
int GrafoRandomizado::getMenorCusto() const {
    return (menorCusto == INT_MAX) ? -1 : menorCusto;
}
