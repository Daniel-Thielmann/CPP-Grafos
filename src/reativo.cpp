#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>

const double INF = 1e18;

//---------------------------------------------------------------------
// calculateCost: Verifica conexões inválidas
//---------------------------------------------------------------------
double calculateCost(int* route, int n, double** costMatrix) {
    double cost = 0;
    for (int i = 0; i < n; i++) {
        if (costMatrix[route[i]][route[i+1]] >= INF) return INF;
        cost += costMatrix[route[i]][route[i+1]];
    }
    return cost;
}

//---------------------------------------------------------------------
// sortCandidates: Ordenação por inserção mais eficiente para pequenos n
//---------------------------------------------------------------------
void sortCandidates(int* candidates, int count, int current, double** costMatrix) {
    for (int i = 1; i < count; i++) {
        int key = candidates[i];
        int j = i - 1;
        while (j >= 0 && costMatrix[current][candidates[j]] > costMatrix[current][key]) {
            candidates[j + 1] = candidates[j];
            j--;
        }
        candidates[j + 1] = key;
    }
}

//---------------------------------------------------------------------
// greedyRandomizedConstruction: Versão corrigida
//---------------------------------------------------------------------
int* greedyRandomizedConstruction(double** costMatrix, int n, double alpha, int start) {
    bool* visited = new bool[n]();
    int* route = new int[n+1];
    int current = start;
    route[0] = current;
    visited[current] = true;

    int* candidates = new int[n];
    int* rcl = new int[n];

    for (int step = 1; step < n; step++) {
        int candidateCount = 0;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && costMatrix[current][j] < INF) {
                candidates[candidateCount++] = j;
            }
        }

        if (candidateCount == 0) {
            delete[] visited; delete[] candidates; delete[] rcl; delete[] route;
            return nullptr;
        }

        sortCandidates(candidates, candidateCount, current, costMatrix);

        double c_min = costMatrix[current][candidates[0]];
        double c_max = costMatrix[current][candidates[candidateCount-1]];
        double threshold = c_min + alpha * (c_max - c_min);

        int rclCount = 0;
        while (rclCount < candidateCount && costMatrix[current][candidates[rclCount]] <= threshold) {
            rcl[rclCount] = candidates[rclCount]; // Correção aplicada
            rclCount++;                            // Incremento seguro
        }

        int selected = (rclCount > 0) ? rcl[rand() % rclCount] : candidates[0];
        route[step] = selected;
        visited[selected] = true;
        current = selected;
    }

    if (costMatrix[current][start] >= INF) {
        delete[] visited; delete[] candidates; delete[] rcl; delete[] route;
        return nullptr;
    }

    route[n] = start;
    delete[] visited; delete[] candidates; delete[] rcl;
    return route;
}

//---------------------------------------------------------------------
// twoOpt: Implementação manual da reversão
//---------------------------------------------------------------------
int* twoOpt(int* route, int n, double** costMatrix) {
    int* bestRoute = new int[n+1];
    // Substitui std::copy por loop manual
    for(int i = 0; i <= n; i++) {
        bestRoute[i] = route[i];
    }
    
    bool improvement = true;
    while (improvement) {
        improvement = false;
        for (int i = 1; i < n-1; i++) {
            for (int j = i+1; j < n; j++) {
                int a = bestRoute[i-1], b = bestRoute[i];
                int c = bestRoute[j], d = bestRoute[j+1];
                
                if (costMatrix[a][c] >= INF || costMatrix[b][d] >= INF) continue;
                
                double delta = costMatrix[a][c] + costMatrix[b][d] 
                             - costMatrix[a][b] - costMatrix[c][d];
                
                if (delta < -1e-9) {
                    // Reversão manual do segmento
                    int start = i;
                    int end = j;
                    while(start < end) {
                        int temp = bestRoute[start];
                        bestRoute[start] = bestRoute[end];
                        bestRoute[end] = temp;
                        start++;
                        end--;
                    }
                    improvement = true;
                }
            }
        }
    }
    return bestRoute;
}

//---------------------------------------------------------------------
// reactiveGRASP: Seleção adaptativa aprimorada
//---------------------------------------------------------------------
int* reactiveGRASP(double** costMatrix, int n, int maxIterations) {
    const int numAlphas = 5;
    double alphas[] = {0.1, 0.3, 0.5, 0.7, 0.9};
    double prob[numAlphas] = {0.2, 0.2, 0.2, 0.2, 0.2};
    double avg[numAlphas] = {0};
    int count[numAlphas] = {0};
    
    int* bestSolution = nullptr;
    double bestCost = INF;
    std::srand(std::time(nullptr));

    for (int iter = 0; iter < maxIterations; iter++) {
        int alphaIndex = 0;
        double r = (double)std::rand() / RAND_MAX;
        while (r > prob[alphaIndex] && alphaIndex < numAlphas-1) {
            r -= prob[alphaIndex];
            alphaIndex++;
        }

        int startNode = std::rand() % n; // Início aleatório
        int* sol = greedyRandomizedConstruction(costMatrix, n, alphas[alphaIndex], startNode);
        if (!sol) continue;

        int* improved = twoOpt(sol, n, costMatrix);
        delete[] sol;
        
        double cost = calculateCost(improved, n, costMatrix);
        if (cost < bestCost) {
            delete[] bestSolution;
            bestSolution = improved;
            bestCost = cost;
        } else {
            delete[] improved;
        }

        avg[alphaIndex] = (avg[alphaIndex] * count[alphaIndex] + cost) / (count[alphaIndex] + 1);
        count[alphaIndex]++;

        double total = 0;
        for (int i = 0; i < numAlphas; i++) {
            double weight = (count[i] == 0) ? 1.0 : bestCost / avg[i];
            prob[i] = weight;
            total += weight;
        }
        for (int i = 0; i < numAlphas; i++) prob[i] /= total;
    }
    
    return bestSolution;
}