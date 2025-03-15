#include <iostream>
#include "./include/grafo_matriz.h"
#include "./include/ListaAdj.h"
#include "./include/grafo_lista.h"
#include "reativo.h"
#include "mtx_loader.h"

using namespace std;

int main() {
    
    cout << "Iniciando o programa!" << endl;

    // Constante para "infinito"
    const double INF = 1e9;

    // Ponteiros para os grafos
    GrafoMatriz* grafoMatriz = nullptr;
    GrafoLista* grafoLista = nullptr;

    string arquivo = "entradas/grafo_100.mtx";
    cout << "Tentando carregar o arquivo: " << arquivo << endl;
    
    MTXLoader::carregarMTX(arquivo, grafoMatriz, grafoLista);

    ///////////////////////////////GRAFO MATRIZ/////////////////////////////////////
    // Imprimindo o grafo
    cout << "Grafo Matriz:" << endl << endl;
   // grafoMatriz->imprimirGrafo();

    // Construir matriz de custos a partir da matriz de adjacência
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

    // Medindo o tempo de execução do GRASP reativo para o grafo matriz
    clock_t startMatriz = clock();
    int* melhorRotaMatriz = reactiveGRASP(costMatrixMatriz, nMatriz, maxIterationsMatriz);
    clock_t endMatriz = clock();
    double custoMelhorRotaMatriz = calculateCost(melhorRotaMatriz, nMatriz, costMatrixMatriz);
    double elapsedMatriz= double(endMatriz - startMatriz) / CLOCKS_PER_SEC;


    // Exibir resultados para o grafo matriz
    cout << "\n--- Resultado do GRASP Reativo com 2-Opt ---\n";
    cout << "\n--- Resultado para Grafo Matriz ---\n" << endl;
    cout << "Melhor rota encontrada: ";
    for (int i = 0; i <= nMatriz; i++) {
        cout << melhorRotaMatriz[i] << " ";
    }
    cout << "\nCusto total: " << custoMelhorRotaMatriz << endl;
    cout << "Tempo de execução (Grafo Matriz): " << elapsedMatriz << " segundos" << endl << endl;
    // Liberação de memória para a matriz de custos (Grafo Matriz)
    delete[] melhorRotaMatriz;
    for (int i = 0; i < nMatriz; i++) {
        delete[] costMatrixMatriz[i];
    }
    delete[] costMatrixMatriz;

    ///////////////////////////////GRAFO LISTA///////////////////////////////////////////
    // Imprimindo o grafo
    cout << "Grafo Lista:" << endl << endl;
  //  grafoLista->imprimirGrafo();

    // Construir matriz de custos a partir do grafo lista
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

    // Medindo o tempo de execução do GRASP reativo para o grafo lista
    clock_t startLista = clock();
    int* melhorRotaLista = reactiveGRASP(costMatrixLista, nLista, maxIterationsLista);
    clock_t endLista = clock();
    double custoMelhorRotaLista = calculateCost(melhorRotaLista, nLista, costMatrixLista);
    double elapsedLista = double(endLista - startLista) / CLOCKS_PER_SEC;

    // Exibir resultados para o grafo lista
    cout << "\n--- Resultado do GRASP Reativo com 2-Opt ---\n";
    cout << "\n--- Resultado para Grafo Lista -> Lista de Adjacência ---\n";
    cout << "Melhor rota: ";
    for (int i = 0; i <= nLista; i++) {
        cout << melhorRotaLista[i] << " ";
    }
    cout << "\nCusto total: " << custoMelhorRotaLista << endl;
   cout << "Tempo de execução (Grafo Lista): " << elapsedLista << " segundos" << endl;
   
    // Liberação de memória para a matriz de custos (Grafo Lista)
    delete[] melhorRotaLista;
    for (int i = 0; i < nLista; i++) {
        delete[] costMatrixLista[i];
    }
    delete[] costMatrixLista;

    // Se os grafos foram alocados dinamicamente, pode ser necessário liberar a memória:
    delete grafoMatriz;
    delete grafoLista;

    return 0;
}
