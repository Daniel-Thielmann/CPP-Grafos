#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "grafo_matriz.h"
#include "grafo_lista.h"
#include "tsp_loader.h"
#include "reativo.h"
#include "guloso.h"
#include "grafo_randomizado.h"

using namespace std;

void processarGrafo(const string& arquivoEntrada) {
    cout << "[LOG] Iniciando processamento do grafo: " << arquivoEntrada << endl;

    // Criando ponteiros para os grafos
    GrafoMatriz* grafoMatriz = nullptr;
    GrafoLista* grafoLista = nullptr;

    // Carregar o grafo da instância TSP
    TSPLoader::carregarTSP(arquivoEntrada, grafoMatriz, grafoLista);

    if (!grafoMatriz || !grafoLista) {
        cerr << "[ERRO] Falha ao carregar o grafo." << endl;
        return;
    }

    // Verificar número de vértices
    cout << "[LOG] Numero de vertices carregados: " << grafoMatriz->getNumVertices() << endl;

    // Exibir a matriz de adjacência (se for pequena, para evitar travamento)
    if (grafoMatriz->getNumVertices() <= 10) {
        cout << "[LOG] Impressao do Grafo Matriz (limite de 10 nos para exibicao)..." << endl;
        grafoMatriz->imprimirGrafo();
    }

    const int INF = 1e9;

    // ==================== PROCESSAMENTO DO GRAFO MATRIZ ====================
    cout << "[LOG] Iniciando processamento com Grafo Matriz..." << endl;
    
    int nMatriz = grafoMatriz->getNumVertices();
    if (nMatriz <= 0) {
        cerr << "[ERRO] Numero invalido de vertices!" << endl;
        return;
    }

    cout << "[DEBUG] Tentando alocar matriz de custos para " << nMatriz << " vertices..." << endl;
    double** costMatrixMatriz = new double*[nMatriz];

   for (int i = 0; i < nMatriz; i++) {
        costMatrixMatriz[i] = new double[nMatriz];
        for (int j = 0; j < nMatriz; j++) {
            if ((i * nMatriz + j) % 1000 == 0) { // Apenas a cada 1000 acessos
                cout << "[DEBUG] Pegando peso da aresta (" << i << "," << j << ")..." << endl;
            }
            int peso = grafoMatriz->getPesoAresta(i, j);
            costMatrixMatriz[i][j] = (peso == -1) ? INF : peso;
        }
    }

    cout << "[DEBUG] Matriz de custos alocada com sucesso!" << endl;

    // Executando GRASP Reativo
    cout << "[LOG] Executando GRASP Reativo..." << endl;
    int maxIterationsMatriz = 1000;
    clock_t startGRASP = clock();
    int* melhorRotaGRASP = reactiveGRASP(costMatrixMatriz, nMatriz, maxIterationsMatriz);
    clock_t endGRASP = clock();

    if (!melhorRotaGRASP) {
        cerr << "[ERRO] Ponteiro melhorRotaGRASP está nulo!" << endl;
        return;
    }

    double custoGRASP = calculateCost(melhorRotaGRASP, nMatriz, costMatrixMatriz);
    double tempoGRASP = double(endGRASP - startGRASP) / CLOCKS_PER_SEC;

    cout << "[RESULTADO] Melhor Rota (GRASP): ";
    for (int i = 0; i < nMatriz; i++) {
        cout << melhorRotaGRASP[i] << " ";
    }
    cout << "\n[RESULTADO] Custo Total (GRASP): " << custoGRASP << endl;
    cout << "[RESULTADO] Tempo de Execucao (GRASP): " << tempoGRASP << " segundos" << endl;

    // Executando Algoritmo Guloso
    cout << "[LOG] Executando Algoritmo Guloso..." << endl;
    Guloso guloso;
    clock_t startGuloso = clock();
    guloso.resolverTSPMatriz(*grafoMatriz);
    clock_t endGuloso = clock();
    double tempoGuloso = double(endGuloso - startGuloso) / CLOCKS_PER_SEC;

    cout << "[RESULTADO] Melhor Rota (Guloso): ";
    int tamanhoGuloso;
    int* melhorRotaGuloso = guloso.getMelhorRota(tamanhoGuloso);
    for (int i = 0; i < tamanhoGuloso; i++) {
        cout << melhorRotaGuloso[i] << " ";
    }
    cout << "\n[RESULTADO] Custo Total (Guloso): " << guloso.getMenorCusto() << endl;
    cout << "[RESULTADO] Tempo de Execucao (Guloso): " << tempoGuloso << " segundos" << endl;

    // Executando Algoritmo Randomizado
    cout << "[LOG] Executando Algoritmo Randomizado..." << endl;
    GrafoRandomizado randomizado(*grafoMatriz);
    clock_t startRandom = clock();
    randomizado.resolver(1000);
    clock_t endRandom = clock();
    double tempoRandom = double(endRandom - startRandom) / CLOCKS_PER_SEC;

    cout << "[RESULTADO] Melhor Rota (Randomizado): ";
    randomizado.exibirMelhorRota();
    cout << "[RESULTADO] Tempo de Execucao (Randomizado): " << tempoRandom << " segundos" << endl;

    // Liberação de memória
    delete[] melhorRotaGRASP;
    for (int i = 0; i < nMatriz; i++) {
        delete[] costMatrixMatriz[i];
    }
    delete[] costMatrixMatriz;

    delete grafoMatriz;
    delete grafoLista;

    cout << "[LOG] Processamento concluido!" << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "[ERRO] Uso incorreto! Formato: ./main.exe -p -m <arquivo_tsp>" << endl;
        return 1;
    }

    string flag1 = argv[1];
    string flag2 = argv[2];

    if (flag1 == "-p" && flag2 == "-m" && argc == 4) {
        string arquivoEntrada = argv[3];
        processarGrafo(arquivoEntrada);
    } else {
        cerr << "[ERRO] Opções inválidas!" << endl;
        return 1;
    }

    return 0;
}
