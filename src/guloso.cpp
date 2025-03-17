#include "guloso.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>

using namespace std;

// 🔥 Função para calcular a melhora na troca 2-opt
double deltaTroca(const int* rota, int i, int k, const GrafoMatriz& grafo) {
    int antes = rota[i], depois = rota[k];
    int antesNovo = rota[k + 1], depoisNovo = rota[i - 1];

    double delta = grafo.getPesoAresta(antes, depois) + grafo.getPesoAresta(antesNovo, depoisNovo) -
                   grafo.getPesoAresta(antes, antesNovo) - grafo.getPesoAresta(depois, depoisNovo);
    return delta;
}

// 🔥 Heurística 2-opt para melhorar a solução inicial
void aplicar2Opt(int* rota, int numCidades, const GrafoMatriz& grafo) {
    bool melhorou = true;
    while (melhorou) {
        melhorou = false;
        for (int i = 1; i < numCidades - 1; i++) {
            for (int k = i + 1; k < numCidades; k++) {
                double delta = deltaTroca(rota, i, k, grafo);
                if (delta < 0) {
                    while (i < k) {
                        swap(rota[i], rota[k]);
                        i++;
                        k--;
                    }
                    melhorou = true;
                }
            }
        }
    }
}

// 🔥 Algoritmo Guloso com pré-processamento eficiente
void Guloso::resolverTSPMatriz(const GrafoMatriz& grafo) {
    numCidades = grafo.getNumVertices();
    melhorRotaIndex = 0;
    menorCusto = numeric_limits<int>::max();

    cout << "[LOG] Iniciando Algoritmo Guloso com " << numCidades << " cidades..." << endl;
    clock_t startTime = clock();

    int numIteracoes = min(numCidades, 100); 

    for (int verticeInicial = 0; verticeInicial < numIteracoes; verticeInicial++) {
        bool visitado[numCidades] = {false};
        int caminho[numCidades], custoTotal = 0, caminhoIndex = 0, atual = verticeInicial;

        caminho[caminhoIndex++] = verticeInicial;
        visitado[verticeInicial] = true;

        for (int i = 1; i < numCidades; i++) {
            int proximoCidade = -1;
            int menorDistancia = numeric_limits<int>::max();

            for (int j = 0; j < numCidades; j++) {
                if (!visitado[j] && grafo.getPesoAresta(atual, j) < menorDistancia) {
                    menorDistancia = grafo.getPesoAresta(atual, j);
                    proximoCidade = j;
                }
            }

            if (proximoCidade == -1) break;

            caminho[caminhoIndex++] = proximoCidade;
            visitado[proximoCidade] = true;
            custoTotal += menorDistancia;
            atual = proximoCidade;
        }

        custoTotal += grafo.getPesoAresta(atual, verticeInicial); 

        if (custoTotal < menorCusto) {
            menorCusto = custoTotal;
            if (melhorRota) delete[] melhorRota;
            melhorRota = new int[caminhoIndex];
            for (int i = 0; i < caminhoIndex; i++) melhorRota[i] = caminho[i];
            melhorRotaIndex = caminhoIndex;
        }

        if (verticeInicial % 10 == 0 || verticeInicial == numIteracoes - 1) {
            double elapsedSeconds = double(clock() - startTime) / CLOCKS_PER_SEC;
            cout << "[LOG] Cidade inicial " << verticeInicial
                 << " | Melhor custo atual: " << menorCusto
                 << " | Tempo decorrido: " << elapsedSeconds << "s" << endl;
        }
    }

    cout << "[LOG] Algoritmo Guloso finalizado. Melhor custo encontrado: " << menorCusto << endl;
}

// 🔥 Estrutura para armazenar vizinhos ordenados
struct VizinhosOrdenados {
    int cidade;
    int distancia;
};

// 🔥 Algoritmo Guloso na Lista com busca eficiente
void Guloso::resolverTSPLista(const GrafoLista& grafo) {
    numCidades = grafo.getNumVertices();
    melhorRotaIndex = 0;
    menorCusto = numeric_limits<int>::max();

    cout << "[LOG] Iniciando Algoritmo Guloso na Lista com " << numCidades << " cidades..." << endl;
    clock_t startTime = clock();

    int numIteracoes = min(numCidades, 100);

    bool visitado[numCidades];
    int caminho[numCidades];

    for (int verticeInicial = 0; verticeInicial < numIteracoes; verticeInicial++) {
        memset(visitado, false, sizeof(visitado));
        int caminhoIndex = 0, custoTotal = 0, atual = verticeInicial;

        caminho[caminhoIndex++] = verticeInicial;
        visitado[verticeInicial] = true;

        for (int i = 1; i < numCidades; i++) {
            int proximoCidade = -1, menorDistancia = numeric_limits<int>::max();
            int tamanho = 0;
            pair<int, int>* vizinhos = grafo.getArestas(atual, tamanho);

            for (int j = 0; j < tamanho; j++) {
                int cidade = vizinhos[j].first;
                int distancia = vizinhos[j].second;

                if (!visitado[cidade] && distancia < menorDistancia) {
                    menorDistancia = distancia;
                    proximoCidade = cidade;
                }
            }
            delete[] vizinhos;

            if (proximoCidade == -1) break;

            caminho[caminhoIndex++] = proximoCidade;
            visitado[proximoCidade] = true;
            custoTotal += menorDistancia;
            atual = proximoCidade;
        }

        int tamanho = 0;
        pair<int, int>* vizinhos = grafo.getArestas(atual, tamanho);
        bool retornoValido = false;

        for (int j = 0; j < tamanho; j++) {
            if (vizinhos[j].first == verticeInicial) {
                caminho[caminhoIndex++] = verticeInicial;
                custoTotal += vizinhos[j].second;
                retornoValido = true;
                break;
            }
        }
        delete[] vizinhos;

        if (retornoValido && custoTotal < menorCusto) {
            menorCusto = custoTotal;
            if (melhorRota) delete[] melhorRota;
            melhorRota = new int[caminhoIndex];
            for (int i = 0; i < caminhoIndex; i++) melhorRota[i] = caminho[i];
            melhorRotaIndex = caminhoIndex;
        }

        if (verticeInicial % 10 == 0 || verticeInicial == numIteracoes - 1) {
            double elapsedSeconds = double(clock() - startTime) / CLOCKS_PER_SEC;
            cout << "[LOG] Cidade inicial " << verticeInicial
                 << " | Melhor custo atual: " << menorCusto
                 << " | Tempo decorrido: " << elapsedSeconds << "s" << endl;
        }
    }

    cout << "[LOG] Algoritmo Guloso (Lista) finalizado. Melhor custo encontrado: " << menorCusto << endl;
}

// Funções para obter resultados
int* Guloso::getMelhorRota(int& tamanho) const {
    tamanho = melhorRotaIndex;
    return melhorRota;
}

int Guloso::getMenorCusto() const {
    return menorCusto;
}

int Guloso::getNumCidades() const {
    return numCidades;
}
