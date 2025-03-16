#include "reativo.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
using namespace std;



//---------------------------------------------------------------------
// calculateCost: (O(n))
//---------------------------------------------------------------------
double calculateCost(int* route, int n, double** costMatrix) {
    double cost = 0;
    for (int i = 0; i < n; i++) {
        cost += costMatrix[route[i]][route[i+1]];
    }
    return cost;
}

//---------------------------------------------------------------------
// sortCandidates: ordenação por seleção 
//---------------------------------------------------------------------
void sortCandidates(int* candidates, int count, int current, double** costMatrix) {
    for (int i = 0; i < count - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < count; j++) {
            if (costMatrix[current][candidates[j]] < costMatrix[current][candidates[minIndex]])
                minIndex = j;
        }
        int temp = candidates[i];
        candidates[i] = candidates[minIndex];
        candidates[minIndex] = temp;
    }
}

//---------------------------------------------------------------------
// greedyRandomizedConstruction: pré-alocação manual
//---------------------------------------------------------------------
int* greedyRandomizedConstruction(double** costMatrix, int n, double alpha) {
    bool* visited = new bool[n](); // Inicializa com false
    int* route = new int[n+1];
    int current = 0;
    route[0] = current;
    visited[current] = true;

    // Buffers pré-alocados
    int* candidates = new int[n];
    int* rcl = new int[n];
    
    for (int step = 1; step < n; step++) {
        int candidateCount = 0;
        for (int j = 0; j < n; j++) {
            if (!visited[j]) candidates[candidateCount++] = j;
        }
        
        sortCandidates(candidates, candidateCount, current, costMatrix);
        
        double c_min = costMatrix[current][candidates[0]];
        double c_max = costMatrix[current][candidates[candidateCount-1]];
        double threshold = c_min + alpha * (c_max - c_min);
        
        int rclCount = 0;
        for (int i = 0; i < candidateCount; i++) {
            if (costMatrix[current][candidates[i]] <= threshold) {
                rcl[rclCount++] = candidates[i];
            } else break; // Aproveita a ordenação
        }
        
        int selected = (rclCount > 0) ? rcl[rand() % rclCount] : candidates[0];
        route[step] = selected;
        visited[selected] = true;
        current = selected;
    }
    
    route[n] = 0;
    delete[] candidates;
    delete[] rcl;
    delete[] visited;
    return route;
}

//---------------------------------------------------------------------
// twoOpt: delta evaluation e reversão in-place (O(n²))
//---------------------------------------------------------------------
int* twoOpt(int* route, int n, double** costMatrix) {
    int* bestRoute = new int[n+1];
    for (int i = 0; i <= n; i++) bestRoute[i] = route[i];
    
    double bestCost = calculateCost(bestRoute, n, costMatrix);
    bool improvement = true;
    
    while (improvement) {
        improvement = false;
        for (int i = 1; i < n-1; i++) {
            for (int j = i+1; j < n; j++) {
                // Delta evaluation (O(1))
                int a = bestRoute[i-1], b = bestRoute[i];
                int c = bestRoute[j], d = bestRoute[j+1];
                double delta = costMatrix[a][c] + costMatrix[b][d] 
                             - costMatrix[a][b] - costMatrix[c][d];
                
                if (delta < -1e-9) {
                    // Reversão in-place
                    for (int k = i, l = j; k < l; k++, l--) {
                        int temp = bestRoute[k];
                        bestRoute[k] = bestRoute[l];
                        bestRoute[l] = temp;
                    }
                    bestCost += delta;
                    improvement = true;
                }
            }
        }
    }
    return bestRoute;
}

//---------------------------------------------------------------------
// reactiveGRASP: otimizado com arrays estáticos para alphas
//---------------------------------------------------------------------
int* reactiveGRASP(double** costMatrix, int n, int maxIterations) {
    double bestCost = INF;
    int* bestSolution = nullptr;

    for (int iter = 0; iter < maxIterations; iter++) {
        int* solution = new int[n+1];
        for (int i = 0; i < n; i++) {
            solution[i] = i;
        }
        solution[n] = solution[0];

        double solCost = calculateCost(solution, n, costMatrix);

        if (solCost < bestCost) {
            delete[] bestSolution;
            bestSolution = solution;
            bestCost = solCost;
        } else {
            delete[] solution;
        }

        if (iter % 100 == 0) {
            cout << "[LOG] Iteracao " << iter << " concluida, melhor custo ate agora: " << bestCost << endl;
        }
    }

    return bestSolution;
}