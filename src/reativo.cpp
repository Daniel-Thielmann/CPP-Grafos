#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <cstdarg>
#include <ctime>
#include <string>
#include "mtx_loader.h"
#include "ListaAdj.h"
#include "reativo.h"

using namespace std;

// Constante para "infinito"
const double INF = 1e9;

//---------------------------------------------------------------------
// Função calculateCost: calcula o custo total de uma rota.
// route: array de inteiros com tamanho n+1 (n cidades e retorno à cidade inicial)
// costMatrix: matriz de custos (dimensão n x n)
//---------------------------------------------------------------------
double calculateCost(int* route, int n, double** costMatrix) {
    double cost = 0;
    for (int i = 0; i < n; i++) {
        cost += costMatrix[ route[i] ][ route[i+1] ];
    }
    return cost;
}

//---------------------------------------------------------------------
// Função sortCandidates: ordena um array de candidatos (por seleção)
// de acordo com o custo da aresta do vértice current.
// candidates: array de índices candidatos (tamanho count)
// current: vértice atual
// costMatrix: matriz de custos
//---------------------------------------------------------------------
void sortCandidates(int* candidates, int count, int current, double** costMatrix) {
    for (int i = 0; i < count - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < count; j++) {
            if ( costMatrix[current][ candidates[j] ] < costMatrix[current][ candidates[minIndex] ] )
                minIndex = j;
        }
        int temp = candidates[i];
        candidates[i] = candidates[minIndex];
        candidates[minIndex] = temp;
    }
}

//---------------------------------------------------------------------
// Função greedyRandomizedConstruction: constrói uma solução para o TSP
// usando uma abordagem gulosa randomizada com RCL (Restricted Candidate List).
// costMatrix: matriz de custos (dimensão n x n)
// n: número de cidades
// alpha: parâmetro de controle (0 <= alpha <= 1)
// Retorna um array de inteiros (tamanho n+1) representando a rota (fechada).
//---------------------------------------------------------------------
int* greedyRandomizedConstruction(double** costMatrix, int n, double alpha) {
    bool* visited = new bool[n];
    for (int i = 0; i < n; i++)
        visited[i] = false;
    
    int* route = new int[n+1];
    int routeIndex = 0;
    int current = 0;
    route[routeIndex++] = current;
    visited[current] = true;
    
    for (int step = 1; step < n; step++) {
        // Cria lista de candidatos (vértices não visitados)
        int candidateCount = 0;
        int* candidates = new int[n];
        for (int j = 0; j < n; j++) {
            if (!visited[j])
                candidates[candidateCount++] = j;
        }
        // Ordena os candidatos pelo custo de 'current'
        sortCandidates(candidates, candidateCount, current, costMatrix);
        double c_min = costMatrix[current][ candidates[0] ];
        double c_max = costMatrix[current][ candidates[candidateCount-1] ];
        
        // Cria a RCL com os candidatos cujo custo é <= c_min + alpha*(c_max - c_min)
        int rclCount = 0;
        int* rcl = new int[candidateCount];
        for (int i = 0; i < candidateCount; i++) {
            double costCandidate = costMatrix[current][ candidates[i] ];
            if (costCandidate <= c_min + alpha * (c_max - c_min))
                rcl[rclCount++] = candidates[i];
        }
        
        // Seleciona aleatoriamente um candidato da RCL
        int selected;
        if (rclCount > 0)
            selected = rcl[rand() % rclCount];
        else
            selected = candidates[0];
        
        route[routeIndex++] = selected;
        visited[selected] = true;
        current = selected;
        
        delete [] candidates;
        delete [] rcl;
    }
    // Fecha o ciclo retornando à cidade inicial
    route[routeIndex] = 0;
    delete [] visited;
    return route;
}

//---------------------------------------------------------------------
// Função twoOpt: aplica a busca local 2‑Opt para melhorar a solução.
// route: solução inicial (array de tamanho n+1)
// n: número de cidades
// costMatrix: matriz de custos
// Retorna uma nova rota (array de tamanho n+1) com melhoria, se encontrada.
//---------------------------------------------------------------------
int* twoOpt(int* route, int n, double** costMatrix) {
    int* bestRoute = new int[n+1];
    for (int i = 0; i < n+1; i++)
        bestRoute[i] = route[i];
    double bestCost = calculateCost(bestRoute, n, costMatrix);
    bool improvement = true;
    
    while (improvement) {
        improvement = false;
        for (int i = 1; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                int* newRoute = new int[n+1];
                // Copia a parte inicial [0, i-1]
                for (int k = 0; k < i; k++)
                    newRoute[k] = bestRoute[k];
                // Inverte o segmento de i a j
                int idx = i;
                for (int k = j; k >= i; k--)
                    newRoute[idx++] = bestRoute[k];
                // Copia o restante [j+1, n]
                for (int k = j + 1; k < n+1; k++)
                    newRoute[k] = bestRoute[k];
                
                double newCost = calculateCost(newRoute, n, costMatrix);
                if (newCost < bestCost) {
                    delete [] bestRoute;
                    bestRoute = newRoute;
                    bestCost = newCost;
                    improvement = true;
                    goto restart_loops; // Reinicia a busca ao encontrar melhoria
                }
                delete [] newRoute;
            }
        }
    restart_loops:
        ;
    }
    return bestRoute;
}

//---------------------------------------------------------------------
// Função reactiveGRASP: executa iterações do GRASP reativo, ajustando
// dinamicamente o parâmetro alpha com base no desempenho.
// costMatrix: matriz de custos (dimensão n x n)
// n: número de cidades
// maxIterations: número de iterações a executar
// Retorna a melhor rota encontrada (array de tamanho n+1).
//---------------------------------------------------------------------
int* reactiveGRASP(double** costMatrix, int n, int maxIterations) {
    int numAlphas = 5;
    double alphas[5] = {0.1, 0.3, 0.5, 0.7, 0.9};
    
    // Inicializa probabilidades uniformes para os valores de alpha
    double* prob = new double[numAlphas];
    for (int i = 0; i < numAlphas; i++)
        prob[i] = 1.0 / numAlphas;
    
    // Estatísticas para cada alpha: custo médio e contagem de execuções
    double* avgCost = new double[numAlphas];
    int* countArr = new int[numAlphas];
    for (int i = 0; i < numAlphas; i++) {
        avgCost[i] = 0.0;
        countArr[i] = 0;
    }
    
    int* bestSolution = NULL;
    double bestSolutionCost = 1e12;
    
    for (int iter = 0; iter < maxIterations; iter++) {
        double r = ((double) rand()) / RAND_MAX;
        double cumulative = 0.0;
        int selectedIndex = 0;
        for (int i = 0; i < numAlphas; i++) {
            cumulative += prob[i];
            if (r <= cumulative) {
                selectedIndex = i;
                break;
            }
        }
        double alpha = alphas[selectedIndex];
        
        int* solution = greedyRandomizedConstruction(costMatrix, n, alpha);
        int* improved = twoOpt(solution, n, costMatrix);
        delete [] solution;
        double solCost = calculateCost(improved, n, costMatrix);
        
        if (solCost < bestSolutionCost) {
            if (bestSolution != NULL)
                delete [] bestSolution;
            bestSolution = improved;
            bestSolutionCost = solCost;
        } else {
            delete [] improved;
        }
        
        avgCost[selectedIndex] = (avgCost[selectedIndex] * countArr[selectedIndex] + solCost) / (countArr[selectedIndex] + 1);
        countArr[selectedIndex]++;
        
        double totalWeight = 0.0;
        double* weights = new double[numAlphas];
        for (int i = 0; i < numAlphas; i++) {
            if (countArr[i] == 0)
                weights[i] = 1.0;
            else
                weights[i] = 1.0 / avgCost[i];
            totalWeight += weights[i];
        }
        for (int i = 0; i < numAlphas; i++)
            prob[i] = weights[i] / totalWeight;
        delete [] weights;
    }
    
    delete [] prob;
    delete [] avgCost;
    delete [] countArr;
    
    return bestSolution;
}
