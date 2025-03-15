#include <iostream>
#include "./include/grafo_matriz.h"
#include "./include/ListaAdj.h"
#include "./include/grafo_lista.h"
#include "reativo.h"
#include "tsp_loader.h"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Iniciando o programa!" << endl;

    // Verifica se os argumentos foram passados corretamente
    if (argc < 4) {
        cout << "Uso incorreto! O formato correto é:" << endl;
        cout << "./main.out -p -m <arquivo_de_entrada>" << endl;
        return 1;
    }

    // Usa o arquivo passado na linha de comando
    string arquivo = argv[3];
    cout << "Tentando carregar o arquivo: " << arquivo << endl;

    // Ponteiros para os grafos
    GrafoMatriz* grafoMatriz = nullptr;
    GrafoLista* grafoLista = nullptr;

    // Carregar o grafo a partir do arquivo .tsp
    TSPLoader::carregarTSP(arquivo, grafoMatriz, grafoLista);

    if (!grafoMatriz || !grafoLista) {
        cout << "Erro ao carregar o grafo." << endl;
        return 1;
    }

    cout << "Grafo carregado com sucesso!" << endl;

    /////////////////////////////// GRAFO MATRIZ /////////////////////////////////////
    cout << "\nGrafo Matriz:" << endl;
    const double INF = 1e9;
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

    cout << "\n--- Resultado do GRASP Reativo com 2-Opt ---" << endl;
    cout << "Melhor rota (Grafo Matriz): ";
    for (int i = 0; i <= nMatriz; i++) cout << melhorRotaMatriz[i] << " ";
    cout << "\nCusto total: " << custoMelhorRotaMatriz;
    cout << "\nTempo de execução: " << elapsedMatriz << " segundos\n";

    delete[] melhorRotaMatriz;
    for (int i = 0; i < nMatriz; i++) delete[] costMatrixMatriz[i];
    delete[] costMatrixMatriz;

    /////////////////////////////// GRAFO LISTA /////////////////////////////////////
    cout << "\nGrafo Lista:" << endl;
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

    cout << "\n--- Resultado do GRASP Reativo com 2-Opt ---" << endl;
    cout << "Melhor rota (Grafo Lista): ";
    for (int i = 0; i <= nLista; i++) cout << melhorRotaLista[i] << " ";
    cout << "\nCusto total: " << custoMelhorRotaLista;
    cout << "\nTempo de execução: " << elapsedLista << " segundos\n";

    delete[] melhorRotaLista;
    for (int i = 0; i < nLista; i++) delete[] costMatrixLista[i];
    delete[] costMatrixLista;

    delete grafoMatriz;
    delete grafoLista;

    return 0;
}
