#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "grafo_matriz.h"
#include "grafo_lista.h"
#include "tsp_loader.h"
#include "reativo.h"

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

    // Definição de infinito para cálculos
    const int INF = 1e9;

    // ==================== PROCESSAMENTO DO GRAFO MATRIZ ====================

    cout << "[LOG] Iniciando processamento com Grafo Matriz..." << endl;
    int nMatriz = grafoMatriz->getNumVertices();
    double** costMatrixMatriz = new double*[nMatriz];

    for (int i = 0; i < nMatriz; i++) {
        costMatrixMatriz[i] = new double[nMatriz];
        for (int j = 0; j < nMatriz; j++) {
            int peso = grafoMatriz->getPesoAresta(i, j);
            costMatrixMatriz[i][j] = (peso == -1) ? INF : peso;
        }
    }

    int maxIterationsMatriz = 1000;
    clock_t startMatriz = clock();
    int* melhorRotaMatriz = reactiveGRASP(costMatrixMatriz, nMatriz, maxIterationsMatriz);
    clock_t endMatriz = clock();

    double custoMelhorRotaMatriz = calculateCost(melhorRotaMatriz, nMatriz, costMatrixMatriz);
    double elapsedMatriz = double(endMatriz - startMatriz) / CLOCKS_PER_SEC;

    cout << "[LOG] Melhor rota (Matriz): ";
    for (int i = 0; i <= nMatriz; i++) {
        cout << melhorRotaMatriz[i] << " ";
    }
    cout << "\nCusto total: " << custoMelhorRotaMatriz << endl;
    cout << "Tempo de execução (Matriz): " << elapsedMatriz << " segundos" << endl;

    delete[] melhorRotaMatriz;
    for (int i = 0; i < nMatriz; i++) {
        delete[] costMatrixMatriz[i];
    }
    delete[] costMatrixMatriz;

    // ==================== PROCESSAMENTO DO GRAFO LISTA ====================

    cout << "[LOG] Iniciando processamento com Grafo Lista..." << endl;
    int nLista = grafoLista->getNumVertices();
    double** costMatrixLista = new double*[nLista];

    for (int i = 0; i < nLista; i++) {
        costMatrixLista[i] = new double[nLista];
        for (int j = 0; j < nLista; j++) {
            int peso = grafoLista->getListaAdj().getCusto(i, j);
            costMatrixLista[i][j] = (peso == -1) ? INF : peso;
        }
    }

    int maxIterationsLista = 1000;
    clock_t startLista = clock();
    int* melhorRotaLista = reactiveGRASP(costMatrixLista, nLista, maxIterationsLista);
    clock_t endLista = clock();

    double custoMelhorRotaLista = calculateCost(melhorRotaLista, nLista, costMatrixLista);
    double elapsedLista = double(endLista - startLista) / CLOCKS_PER_SEC;

    cout << "[LOG] Melhor rota (Lista): ";
    for (int i = 0; i <= nLista; i++) {
        cout << melhorRotaLista[i] << " ";
    }
    cout << "\nCusto total: " << custoMelhorRotaLista << endl;
    cout << "Tempo de execução (Lista): " << elapsedLista << " segundos" << endl;

    delete[] melhorRotaLista;
    for (int i = 0; i < nLista; i++) {
        delete[] costMatrixLista[i];
    }
    delete[] costMatrixLista;

    delete grafoMatriz;
    delete grafoLista;

    cout << "[LOG] Processamento concluído!" << endl;
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
