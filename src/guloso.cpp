#include "guloso.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

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

// 🔥 Algoritmo Guloso com pré-processamento para acelerar buscas
void Guloso::resolverTSPMatriz(const GrafoMatriz& grafo) {
    numCidades = grafo.getNumVertices();
    melhorRotaIndex = 0;
    menorCusto = INT_MAX;

    cout << "[LOG] Iniciando Algoritmo Guloso com " << numCidades << " cidades..." << endl;
    clock_t startTime = clock();

    int numIteracoes = min(numCidades, 100); // 🚀 Limita para 100 cidades

    for (int verticeInicial = 0; verticeInicial < numIteracoes; verticeInicial++) {
        bool visitado[numCidades] = {false};
        int caminho[numCidades], custoTotal = 0, caminhoIndex = 0, atual = verticeInicial;

        caminho[caminhoIndex++] = verticeInicial;
        visitado[verticeInicial] = true;

        // 🚀 PRÉ-CÁLCULO: Encontramos a cidade mais próxima para cada cidade
        int cidadeMaisProxima[numCidades];
        for (int i = 0; i < numCidades; i++) cidadeMaisProxima[i] = -1; // 🔥 Garante inicialização segura

        for (int i = 0; i < numCidades; i++) {
            int menorDistancia = INT_MAX, melhorVizinho = -1;
            for (int j = 0; j < numCidades; j++) {
                if (i != j) {
                    int distancia = grafo.getPesoAresta(i, j);
                    if (distancia > 0 && distancia < menorDistancia) {
                        menorDistancia = distancia;
                        melhorVizinho = j;
                    }
                }
            }
            cidadeMaisProxima[i] = melhorVizinho;
        }

        // 🚀 Montamos a rota inicial usando a cidade mais próxima
        for (int i = 1; i < numCidades; i++) {
            int proximoCidade = cidadeMaisProxima[atual];

            // 🔥 Correção: Se `proximoCidade` for inválido, selecionamos o menor válido
            if (proximoCidade == -1 || proximoCidade >= numCidades || proximoCidade < 0 || visitado[proximoCidade]) {
                int menorDistancia = INT_MAX, melhorAlternativa = -1;
                for (int j = 0; j < numCidades; j++) {
                    if (!visitado[j]) {
                        int distancia = grafo.getPesoAresta(atual, j);
                        if (distancia > 0 && distancia < menorDistancia) {
                            menorDistancia = distancia;
                            melhorAlternativa = j;
                        }
                    }
                }
                if (melhorAlternativa != -1) {
                    proximoCidade = melhorAlternativa;
                } else {
                    cout << "[ERRO] Nenhuma cidade válida encontrada para " << atual << ". Encerrando busca." << endl;
                    break;
                }
            }

            caminho[caminhoIndex++] = proximoCidade;
            visitado[proximoCidade] = true;
            int peso = grafo.getPesoAresta(atual, proximoCidade);
            if (peso > 0) custoTotal += peso;
            atual = proximoCidade;
        }

        // 🚀 Fechamos o ciclo para a cidade inicial
        int distanciaRetorno = grafo.getPesoAresta(atual, verticeInicial);
        if (distanciaRetorno > 0) {
            caminho[caminhoIndex++] = verticeInicial;
            custoTotal += distanciaRetorno;
        }

        if (custoTotal < menorCusto) {
            menorCusto = custoTotal;
            if (melhorRota) delete[] melhorRota;
            melhorRota = new int[caminhoIndex];
            for (int i = 0; i < caminhoIndex; i++) melhorRota[i] = caminho[i];
            melhorRotaIndex = caminhoIndex;
        }

        if (verticeInicial % 10 == 0 || verticeInicial == numIteracoes - 1) {
            clock_t elapsedTime = clock() - startTime;
            double elapsedSeconds = double(elapsedTime) / CLOCKS_PER_SEC;
            cout << "[LOG] Processando cidade inicial " << verticeInicial
                 << " de " << numIteracoes
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

// 🔥 Algoritmo Guloso com **pré-processamento eficiente** e **busca otimizada**
void Guloso::resolverTSPLista(const GrafoLista& grafo) {
    numCidades = grafo.getNumVertices();
    melhorRotaIndex = 0;
    menorCusto = std::numeric_limits<int>::max();

    cout << "[LOG] Iniciando Algoritmo Guloso na Lista com " << numCidades << " cidades..." << endl;
    clock_t startTime = clock();

    int numIteracoes = min(numCidades, 100);  // 🚀 Limita a 100 cidades

    // 🚀 **Pré-processamento - Ordenação de vizinhos por distância**
    VizinhosOrdenados vizinhosOrdenados[numCidades][numCidades];
    int numVizinhos[numCidades] = {0};

    cout << "[LOG] Ordenando vizinhos por distância..." << endl;
    for (int i = 0; i < numCidades; i++) {
        int tamanho = 0;
        pair<int, int>* vizinhos = grafo.getArestas(i, tamanho);
        numVizinhos[i] = tamanho;

        for (int j = 0; j < tamanho; j++) {
            vizinhosOrdenados[i][j].cidade = vizinhos[j].first;
            vizinhosOrdenados[i][j].distancia = vizinhos[j].second;
        }

        // 🚀 Ordena os vizinhos por menor distância (Insertion Sort para evitar dependência de `algorithm`)
        for (int j = 1; j < tamanho; j++) {
            VizinhosOrdenados temp = vizinhosOrdenados[i][j];
            int k = j - 1;
            while (k >= 0 && vizinhosOrdenados[i][k].distancia > temp.distancia) {
                vizinhosOrdenados[i][k + 1] = vizinhosOrdenados[i][k];
                k--;
            }
            vizinhosOrdenados[i][k + 1] = temp;
        }
        delete[] vizinhos;
    }

    cout << "[LOG] Vizinhos ordenados com sucesso!" << endl;

    // 🚀 **Alocação otimizada para evitar `new[]` repetidos**
    bool visitado[numCidades];
    int caminho[numCidades];

    for (int verticeInicial = 0; verticeInicial < numIteracoes; verticeInicial++) {
        memset(visitado, false, sizeof(visitado));  // 🚀 Restaura valores sem realocar memória
        int caminhoIndex = 0, custoTotal = 0, atual = verticeInicial;

        caminho[caminhoIndex++] = verticeInicial;
        visitado[verticeInicial] = true;

        cout << "[DEBUG] Iniciando percurso a partir da cidade " << verticeInicial << endl;

        for (int i = 1; i < numCidades; i++) {
            int proximoCidade = -1, menorDistancia = INT_MAX;

            // 🚀 Busca na tabela de vizinhos pré-ordenada
            for (int j = 0; j < numVizinhos[atual]; j++) {
                int cidade = vizinhosOrdenados[atual][j].cidade;
                int distancia = vizinhosOrdenados[atual][j].distancia;

                if (!visitado[cidade]) {
                    proximoCidade = cidade;
                    menorDistancia = distancia;
                    break;  // 🚀 Como a lista já está ordenada, o primeiro válido é o melhor!
                }
            }

            if (proximoCidade == -1) {
                cout << "[ERRO] Nenhum próximo nó válido encontrado. Parando na cidade " << atual << endl;
                break;
            }

            caminho[caminhoIndex++] = proximoCidade;
            visitado[proximoCidade] = true;
            custoTotal += menorDistancia;
            atual = proximoCidade;

            if (i % 10 == 0) {  // Log a cada 10 cidades processadas
                cout << "[LOG] Iteração " << i << " - Cidade Atual: " << atual
                     << " - Melhor custo: " << menorCusto << endl;
            }
        }

        // 🚀 Fechamos o ciclo para a cidade inicial
        int tamanho = numVizinhos[atual];
        bool retornoValido = false;

        for (int j = 0; j < tamanho; j++) {
            if (vizinhosOrdenados[atual][j].cidade == verticeInicial) {
                caminho[caminhoIndex++] = verticeInicial;
                custoTotal += vizinhosOrdenados[atual][j].distancia;
                retornoValido = true;
                break;
            }
        }

        if (retornoValido && custoTotal < menorCusto) {
            menorCusto = custoTotal;
            if (melhorRota) delete[] melhorRota;
            melhorRota = new int[caminhoIndex];
            for (int i = 0; i < caminhoIndex; i++) melhorRota[i] = caminho[i];
            melhorRotaIndex = caminhoIndex;
        }

        if (verticeInicial % 10 == 0 || verticeInicial == numIteracoes - 1) {
            clock_t elapsedTime = clock() - startTime;
            double elapsedSeconds = double(elapsedTime) / CLOCKS_PER_SEC;
            cout << "[LOG] Processando cidade inicial " << verticeInicial
                 << " de " << numIteracoes
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
