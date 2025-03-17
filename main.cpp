#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath> 
#include "grafo_matriz.h"
#include "grafo_lista.h"
#include "tsp_loader.h"
#include "reativo.h"
#include "guloso.h"
#include "grafo_randomizado.h"
#include "util.h"
using namespace std;


void processarGrafo(const string& arquivoEntrada, 
                    double& custoGRASP_Matriz, double& tempoGRASP_Matriz,
                    double& custoGuloso_Matriz, double& tempoGuloso_Matriz,
                    double& custoRandomizado_Matriz, double& tempoRandomizado_Matriz,
                    double& custoGRASP_Lista, double& tempoGRASP_Lista,
                    double& custoGuloso_Lista, double& tempoGuloso_Lista,
                    double& custoRandomizado_Lista, double& tempoRandomizado_Lista) {
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

    cout << "[LOG] Numero de vertices carregados: " << grafoMatriz->getNumVertices() << endl;

    // ==================== PROCESSAMENTO COM MATRIZ ====================
    cout << "[LOG] Iniciando processamento com Grafo Matriz..." << endl;
    
    int nMatriz = grafoMatriz->getNumVertices();
    double** costMatrixMatriz = new double*[nMatriz];

    for (int i = 0; i < nMatriz; i++) {
        costMatrixMatriz[i] = new double[nMatriz];
        for (int j = 0; j < nMatriz; j++) {
            int peso = grafoMatriz->getPesoAresta(i, j);
            costMatrixMatriz[i][j] = (peso == -1) ? 1e9 : peso;
        }
    }

    // Executando GRASP Reativo (Matriz)
    cout << "[LOG] Executando GRASP (Matriz)..." << endl;
    clock_t startGRASP_Matriz = clock();
    int* melhorRotaGRASP = reactiveGRASP(costMatrixMatriz, nMatriz, 1000);
    clock_t endGRASP_Matriz = clock();
    custoGRASP_Matriz = calculateCost(melhorRotaGRASP, nMatriz, costMatrixMatriz);
    tempoGRASP_Matriz = double(endGRASP_Matriz - startGRASP_Matriz) / CLOCKS_PER_SEC;

    // Executando Algoritmo Guloso (Matriz)
    cout << "[LOG] Executando Algoritmo Guloso (Matriz)..." << endl;
    Guloso guloso;
    clock_t startGuloso_Matriz = clock();
    guloso.resolverTSPMatriz(*grafoMatriz);
    clock_t endGuloso_Matriz = clock();
    tempoGuloso_Matriz = double(endGuloso_Matriz - startGuloso_Matriz) / CLOCKS_PER_SEC;
    custoGuloso_Matriz = guloso.getMenorCusto();

    // Executando Algoritmo Randomizado (Matriz)
    cout << "[LOG] Executando Algoritmo Randomizado (Matriz)..." << endl;
    GrafoRandomizado randomizado(*grafoMatriz);
    clock_t startRandom_Matriz = clock();
    randomizado.resolver(1000);
    clock_t endRandom_Matriz = clock();
    tempoRandomizado_Matriz = double(endRandom_Matriz - startRandom_Matriz) / CLOCKS_PER_SEC;
    custoRandomizado_Matriz = randomizado.getMenorCusto();

    // ==================== PROCESSAMENTO COM LISTA ====================
    cout << "[LOG] Iniciando processamento com Grafo Lista..." << endl;
    
    int nLista = grafoLista->getNumVertices();

    // Executando GRASP Reativo (Lista)
    cout << "[LOG] Executando GRASP (Lista)..." << endl;
    clock_t startGRASP_Lista = clock();
    int* melhorRotaGRASP_Lista = reactiveGRASP(costMatrixMatriz, nLista, 1000);
    clock_t endGRASP_Lista = clock();
    custoGRASP_Lista = calculateCost(melhorRotaGRASP_Lista, nLista, costMatrixMatriz);
    tempoGRASP_Lista = double(endGRASP_Lista - startGRASP_Lista) / CLOCKS_PER_SEC;

    // Executando Algoritmo Guloso (Lista)
    cout << "[LOG] Executando Algoritmo Guloso (Lista)..." << endl;
    clock_t startGuloso_Lista = clock();
    guloso.resolverTSPLista(*grafoLista);
    clock_t endGuloso_Lista = clock();
    tempoGuloso_Lista = double(endGuloso_Lista - startGuloso_Lista) / CLOCKS_PER_SEC;
    custoGuloso_Lista = guloso.getMenorCusto();

    // Executando Algoritmo Randomizado (Lista)
    cout << "[LOG] Executando Algoritmo Randomizado (Lista)..." << endl;
    GrafoRandomizado randomizadoLista(*grafoLista);
    clock_t startRandom_Lista = clock();
    randomizadoLista.resolver(1000);
    clock_t endRandom_Lista = clock();
    tempoRandomizado_Lista = double(endRandom_Lista - startRandom_Lista) / CLOCKS_PER_SEC;
    custoRandomizado_Lista = randomizadoLista.getMenorCusto();

    // 🚀 Relatório final comparando Matriz vs Lista
    cout << "\n==================== RELATORIO FINAL ====================" << endl;
    cout << "[RESULTADO FINAL] Comparacao dos Algoritmos (Matriz vs Lista):" << endl;
    cout << " - GRASP (Matriz) -> Custo: " << custoGRASP_Matriz << " | Tempo: " << tempoGRASP_Matriz << " segundos" << endl;
    cout << " - GRASP (Lista)  -> Custo: " << custoGRASP_Lista << " | Tempo: " << tempoGRASP_Lista << " segundos" << endl;
    cout << " - Guloso (Matriz) -> Custo: " << custoGuloso_Matriz << " | Tempo: " << tempoGuloso_Matriz << " segundos" << endl;
    cout << " - Guloso (Lista)  -> Custo: " << custoGuloso_Lista << " | Tempo: " << tempoGuloso_Lista << " segundos" << endl;
    cout << " - Randomizado (Matriz) -> Custo: " << custoRandomizado_Matriz << " | Tempo: " << tempoRandomizado_Matriz << " segundos" << endl;
    cout << " - Randomizado (Lista)  -> Custo: " << custoRandomizado_Lista << " | Tempo: " << tempoRandomizado_Lista << " segundos" << endl;

    cout << "\n[RESULTADO FINAL] Melhor Solucao Encontrada:" << endl;
    double melhorCusto = minValor(minValor(custoGRASP_Matriz, custoGuloso_Matriz, custoRandomizado_Matriz),
                                  minValor(custoGRASP_Lista, custoGuloso_Lista, custoRandomizado_Lista), 1e9);
    cout << " - Melhor Custo Obtido: " << melhorCusto << endl;

    cout << "\n[LOG] Todos os algoritmos foram executados com sucesso!" << endl;
    cout << "=========================================================" << endl;
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

        // Declaração das variáveis de resultado (Matriz)
        double custoGRASP, tempoGRASP;
        double menorCusto, tempoGuloso;
        double custoRandomizado, tempoRandom;

        // Declaração das variáveis de resultado (Lista)
        double custoGRASP_Lista, tempoGRASP_Lista;
        double custoGuloso_Lista, tempoGuloso_Lista;
        double custoRandomizado_Lista, tempoRandomizado_Lista;

        // Chamada da função processarGrafo com todos os parâmetros
        processarGrafo(arquivoEntrada, 
                       custoGRASP, tempoGRASP, 
                       menorCusto, tempoGuloso, 
                       custoRandomizado, tempoRandom, 
                       custoGRASP_Lista, tempoGRASP_Lista, 
                       custoGuloso_Lista, tempoGuloso_Lista, 
                       custoRandomizado_Lista, tempoRandomizado_Lista);
                       
        // 🚀 Relatório final dos algoritmos
        cout << "[RESULTADO FINAL] Comparacao dos Algoritmos:" << endl;
        cout << " - Algoritmo Randomizado -> Custo: " << custoRandomizado << " | Tempo: " << tempoRandom << " segundos" << endl;
        cout << " - Algoritmo Guloso -> Custo: " << menorCusto << " | Tempo: " << tempoGuloso << " segundos" << endl;
        cout << " - Algoritmo GRASP -> Custo: " << custoGRASP << " | Tempo: " << tempoGRASP << " segundos" << endl;

        cout << "\n[RESULTADO FINAL] Melhor Solucao Encontrada:" << endl;
        double melhorCusto = minValor(custoRandomizado, menorCusto, custoGRASP);
        cout << " - Melhor Custo Obtido: " << melhorCusto << endl;

        cout << "\n[LOG] Todos os algoritmos foram executados com sucesso!" << endl;
        cout << "=========================================================" << endl;
    } else {
        cerr << "[ERRO] Opcoes invalidas!" << endl;
        return 1;
    }

    return 0;
}
