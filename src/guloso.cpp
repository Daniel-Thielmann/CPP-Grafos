#include "guloso.h"
#include <iostream>
#include <fstream>

void Guloso::resolverTSPMatriz(const GrafoMatriz& grafo) {
    numCidades = grafo.getNumVertices(); // Obtém o número de cidades
    melhorRotaIndex = 0;  // Reseta o índice da melhor rota
    menorCusto = INT_MAX;

    // Testa todos os vértices como ponto inicial
    for (int verticeInicial = 0; verticeInicial < numCidades; verticeInicial++) {
        bool* visitado = new bool[numCidades]();  // Inicializa todos os valores como falso
        int* caminho = new int[numCidades];       // Array para armazenar o caminho
        int caminhoIndex = 0;                     // Índice do caminho
        int atual = verticeInicial;               // Inicializa corretamente
        int custoTotal = 0;                       // Inicializa corretamente

        caminho[caminhoIndex++] = verticeInicial;
        visitado[verticeInicial] = true;

        for (int i = 1; i < numCidades; i++) {
            int proximo = -1;
            int menorDistancia = INT_MAX;

            int tamanho = 0;
            pair<int, int>* vizinhos = grafo.getArestas(atual, tamanho);  // Obtém vizinhos e pesos

            for (int j = 0; j < tamanho; j++) {
                int cidade = vizinhos[j].first;
                int distancia = vizinhos[j].second;

                if (!visitado[cidade] && distancia < menorDistancia) {
                    menorDistancia = distancia;
                    proximo = cidade;
                }
            }

            if (proximo == -1) {  // Nenhum próximo válido encontrado
                delete[] vizinhos;
                break;
            }

            caminho[caminhoIndex++] = proximo;
            visitado[proximo] = true;
            custoTotal += menorDistancia;
            atual = proximo;

            delete[] vizinhos; // Libera a memória corretamente
        }

        // Retorna à cidade inicial
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

        // Atualiza a melhor rota e o menor custo
        if (custoTotal < menorCusto) {
            menorCusto = custoTotal;

            if (melhorRota != nullptr) { // Evita deletar memória não alocada
                delete[] melhorRota;
            }

            melhorRota = new int[caminhoIndex]; // Aloca memória para a nova melhor rota
            for (int i = 0; i < caminhoIndex; i++) {
                melhorRota[i] = caminho[i];
            }
            melhorRotaIndex = caminhoIndex; // Atualiza o índice da melhor rota
        }

        delete[] visitado; // Libera a memória alocada
        delete[] caminho;  // Libera a memória alocada
    }
}

void Guloso::resolverTSPLista(const GrafoLista& grafo) {
    numCidades = grafo.getNumVertices(); // Obtém o número de cidades
    melhorRotaIndex = 0;  // Reseta o índice da melhor rota
    menorCusto = INT_MAX;

    // Testa todos os vértices como ponto inicial
    for (int verticeInicial = 0; verticeInicial < numCidades; verticeInicial++) {
        bool* visitado = new bool[numCidades]();  // Inicializa todos os valores como falso
        int* caminho = new int[numCidades];       // Array para armazenar o caminho
        int caminhoIndex = 0;                     // Índice do caminho
        int atual = verticeInicial, custoTotal = 0; // Inicializa corretamente

        caminho[caminhoIndex++] = verticeInicial;
        visitado[verticeInicial] = true;

        for (int i = 1; i < numCidades; i++) {
            int proximo = -1;
            int menorDistancia = INT_MAX;

            int tamanho = 0;
            pair<int, int>* vizinhos = grafo.getArestas(atual, tamanho);  // Obtém vizinhos e pesos

            for (int j = 0; j < tamanho; j++) {
                int cidade = vizinhos[j].first;
                int distancia = vizinhos[j].second;

                if (!visitado[cidade] && distancia < menorDistancia) {
                    menorDistancia = distancia;
                    proximo = cidade;
                }
            }

            if (proximo == -1) {  // Nenhum próximo válido encontrado
                delete[] vizinhos;
                break;
            }

            caminho[caminhoIndex++] = proximo;
            visitado[proximo] = true;
            custoTotal += menorDistancia;
            atual = proximo;

            delete[] vizinhos; // Libera a memória corretamente
        }

        // Retorna à cidade inicial
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

        // Atualiza a melhor rota e o menor custo se o caminho for completo
        if (retornoValido && custoTotal < menorCusto) {
            menorCusto = custoTotal;

            if (melhorRota != nullptr) { // Evita deletar memória não alocada
                delete[] melhorRota;
            }

            melhorRota = new int[caminhoIndex]; // Aloca memória para a nova melhor rota
            for (int i = 0; i < caminhoIndex; i++) {
                melhorRota[i] = caminho[i];
            }
            melhorRotaIndex = caminhoIndex; // Atualiza o índice da melhor rota
        }

        delete[] visitado; // Libera a memória alocada
        delete[] caminho;  // Libera a memória alocada
    }
}


// Funções para obter resultados
int* Guloso::getMelhorRota(int& tamanho) const {
    tamanho = melhorRotaIndex;  // Retorna o tamanho da melhor rota
    return melhorRota;
}

int Guloso::getMenorCusto() const {
    return menorCusto;
}

int Guloso::getNumCidades() const {
    return numCidades;
}