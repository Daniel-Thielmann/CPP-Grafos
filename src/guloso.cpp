#include "guloso.h"
#include <iostream>
#include <fstream>

void Guloso::resolverTSPMatriz(const GrafoMatriz& grafo) {
    numCidades = grafo.getNumVertices();
    melhorRotaIndex = 0;
    menorCusto = MAX_INT;

    for (int verticeInicial = 0; verticeInicial < numCidades; verticeInicial++) {
        bool* visitado = new bool[numCidades]();
        int* caminho = new int[numCidades];
        int caminhoIndex = 0, custoTotal = 0, atual = verticeInicial;

        caminho[caminhoIndex++] = verticeInicial;
        visitado[verticeInicial] = true;

        for (int i = 1; i < numCidades; i++) {
            int proximo = -1, menorDistancia = MAX_INT;
            int tamanho = 0;
            pair<int, int>* vizinhos = grafo.getArestas(atual, tamanho);

            for (int j = 0; j < tamanho; j++) {
                int cidade = vizinhos[j].first;
                int distancia = vizinhos[j].second;

                if (!visitado[cidade] && distancia < menorDistancia) {
                    menorDistancia = distancia;
                    proximo = cidade;
                }
            }

            delete[] vizinhos;

            if (proximo == -1) {
                break;
            }

            caminho[caminhoIndex++] = proximo;
            visitado[proximo] = true;
            custoTotal += menorDistancia;
            atual = proximo;
        }

        int tamanho = 0;
        pair<int, int>* vizinhos = grafo.getArestas(atual, tamanho);
        for (int j = 0; j < tamanho; j++) {
            if (vizinhos[j].first == verticeInicial) {
                caminho[caminhoIndex++] = verticeInicial;
                custoTotal += vizinhos[j].second;
                break;
            }
        }
        delete[] vizinhos;

        if (custoTotal < menorCusto) {
            menorCusto = custoTotal;
            if (melhorRota) delete[] melhorRota;
            melhorRota = new int[caminhoIndex];
            for (int i = 0; i < caminhoIndex; i++) melhorRota[i] = caminho[i];
            melhorRotaIndex = caminhoIndex;
        }

        delete[] visitado;
        delete[] caminho;
    }
}

void Guloso::resolverTSPLista(const GrafoLista& grafo) {
    numCidades = grafo.getNumVertices();
    melhorRotaIndex = 0;
    menorCusto = MAX_INT;

    for (int verticeInicial = 0; verticeInicial < numCidades; verticeInicial++) {
        bool* visitado = new bool[numCidades]();
        int* caminho = new int[numCidades];
        int caminhoIndex = 0, custoTotal = 0, atual = verticeInicial;

        caminho[caminhoIndex++] = verticeInicial;
        visitado[verticeInicial] = true;

        for (int i = 1; i < numCidades; i++) {
            int proximo = -1, menorDistancia = MAX_INT;
            int tamanho = 0;
            pair<int, int>* vizinhos = grafo.getArestas(atual, tamanho);

            for (int j = 0; j < tamanho; j++) {
                int cidade = vizinhos[j].first;
                int distancia = vizinhos[j].second;

                if (!visitado[cidade] && distancia < menorDistancia) {
                    menorDistancia = distancia;
                    proximo = cidade;
                }
            }

            delete[] vizinhos;

            if (proximo == -1) {
                break;
            }

            caminho[caminhoIndex++] = proximo;
            visitado[proximo] = true;
            custoTotal += menorDistancia;
            atual = proximo;
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

        delete[] visitado;
        delete[] caminho;
    }
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
