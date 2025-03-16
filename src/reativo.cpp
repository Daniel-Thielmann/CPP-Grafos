// reativo.cpp
#include "reativo.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring> // Para memset

//---------------------------------------------------------------------
// calculateCost: inlined para evitar overhead de chamada
//---------------------------------------------------------------------
inline double calculateCost(int* route, int n, double** costMatrix) {
    double cost = 0.0;
    for (int i = 0; i < n; ++i) {
        cost += costMatrix[route[i]][route[i+1]];
    }
    return cost;
}

//---------------------------------------------------------------------
// sortCandidates: insertion sort com pré-computação de custos
//---------------------------------------------------------------------
void sortCandidates(int* candidates, int count, int current, double** costMatrix) {
    if (count <= 1) return;
    
    // Limita a 100 candidatos para ordenação
    const int maxCandidates = 100;
    if (count > maxCandidates) count = maxCandidates;

    // Insertion sort em subset reduzido
    for (int i = 1; i < count; ++i) {
        int key = candidates[i];
        double keyCost = costMatrix[current][key];
        int j = i - 1;
        while (j >= 0 && costMatrix[current][candidates[j]] > keyCost) {
            candidates[j + 1] = candidates[j];
            --j;
        }
        candidates[j + 1] = key;
    }
}

int* greedyRandomizedConstruction(double** costMatrix, int n, double alpha, GRASPBuffers& buffers) {
    memset(buffers.visited, 0, n * sizeof(bool));
    int* route = buffers.routeBuffer;
    
    // Inicialização com Nearest Neighbor para melhor qualidade
    int current = rand() % n;  // Começa de um nó aleatório para diversificação
    route[0] = current;
    buffers.visited[current] = true;

    for (int step = 1; step < n; ++step) {
        int candidateCount = 0;
        for (int j = 0; j < n; ++j) {
            if (!buffers.visited[j]) buffers.candidates[candidateCount++] = j;
        }
        
        // Ordenação dos 20% melhores candidatos
        const int sortedCandidates = std::fmax(100, (int)(candidateCount * 0.2));
        sortCandidates(buffers.candidates, sortedCandidates, current, costMatrix);
        
        double c_min = costMatrix[current][buffers.candidates[0]];
        double c_max = costMatrix[current][buffers.candidates[sortedCandidates-1]];
        double threshold = c_min + alpha * (c_max - c_min);
        
        int rclCount = 0;
        for (int k = 0; k < sortedCandidates; ++k) {
            if (costMatrix[current][buffers.candidates[k]] <= threshold) {
                buffers.rcl[rclCount++] = buffers.candidates[k];
            }
        }

        int selected = (rclCount > 0) ? buffers.rcl[rand() % rclCount] : buffers.candidates[0];
        route[step] = selected;
        buffers.visited[selected] = true;
        current = selected;
    }
    
    route[n] = route[0];  // Garante ciclo fechado
    return route;
}

template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

int* twoOpt(int* route, int n, double** costMatrix, int* buffer) {
    memcpy(buffer, route, (n+1) * sizeof(int));
    double currentCost = calculateCost(buffer, n, costMatrix);
    const int maxAttempts = n * 0.3;  // Aumenta para 30% das arestas
    const int maxIterations = 20;     // Mais iterações

    for (int iter = 0; iter < maxIterations; ++iter) {
        bool improved = false;
        
        // Estratégia de First Improvement com amostragem
        for (int attempt = 0; attempt < maxAttempts; ++attempt) {
            int i = 1 + rand() % (n-2);
            int j = i + 1 + rand() % (n - i - 1);
            
            // Cálculo delta otimizado
            double delta = costMatrix[buffer[i-1]][buffer[j]] 
                         + costMatrix[buffer[i]][buffer[j+1]]
                         - costMatrix[buffer[i-1]][buffer[i]] 
                         - costMatrix[buffer[j]][buffer[j+1]];
            
            if (delta < -1e-9) {
                // Reversão inteligente: inverte apenas o segmento necessário
                while (i < j) {
                    swap(buffer[i], buffer[j]);
                    i++;
                    j--;
                }
                currentCost += delta;
                improved = true;
                break;
            }
        }
        if (!improved) break;
    }
    return buffer;
}


//---------------------------------------------------------------------
// reactiveGRASP: versão completa com fase de intensificação final
//---------------------------------------------------------------------
int* reactiveGRASP(double** costMatrix, int n, int maxIterations) {
    const int numAlphas = 5;
    double alphas[] = {0.1, 0.3, 0.5, 0.7, 0.9};
    
    // Buffers reutilizáveis
    GRASPBuffers buffers;
    buffers.visited = new bool[n]();
    buffers.candidates = new int[n];
    buffers.rcl = new int[n];
    buffers.routeBuffer = new int[n+1];
    
    int* bestSolution = new int[n+1];
    double bestCost = INF;
    
    // Estado reativo
    double weights[numAlphas];
    double cumulativeProbs[numAlphas] = {0.2, 0.4, 0.6, 0.8, 1.0}; // Distribuição inicial
    double avgCost[numAlphas] = {0};
    int count[numAlphas] = {0};
    
    // Buffer para 2-opt
    int* twoOptBuffer = new int[n+1];
    srand(time(NULL)); // Seed aleatória

    // Fase principal
    for (int iter = 0; iter < maxIterations; ++iter) {
        // Seleção do alpha
        double r = static_cast<double>(rand()) / RAND_MAX;
        int selectedIndex = 0;
        while (selectedIndex < numAlphas-1 && r > cumulativeProbs[selectedIndex]) {
            ++selectedIndex;
        }
        
        // Construção + Busca Local
        int* solution = greedyRandomizedConstruction(costMatrix, n, alphas[selectedIndex], buffers);
        int* improved = twoOpt(solution, n, costMatrix, twoOptBuffer);
        double solCost = calculateCost(improved, n, costMatrix);
        
        // Atualização da melhor solução
        if (solCost < bestCost) {
            memcpy(bestSolution, improved, (n+1) * sizeof(int));
            bestCost = solCost;
        }
        
        // Atualização adaptativa
        avgCost[selectedIndex] = (avgCost[selectedIndex] * count[selectedIndex] + solCost) /
                               (count[selectedIndex] + 1);
        count[selectedIndex]++;
        
        // Atualização das probabilidades
        double totalWeight = 0.0;
        for (int i = 0; i < numAlphas; ++i) {
            weights[i] = (count[i] == 0) ? 1.0 : 1.0 / avgCost[i];
            totalWeight += weights[i];
        }
        
        // Pré-computar probabilidades acumuladas
        cumulativeProbs[0] = weights[0] / totalWeight;
        for (int i = 1; i < numAlphas; ++i) {
            cumulativeProbs[i] = cumulativeProbs[i-1] + (weights[i] / totalWeight);
        }
    }

    // Fase de intensificação final na melhor solução
    int* finalSolution = twoOpt(bestSolution, n, costMatrix, twoOptBuffer);
    double finalCost = calculateCost(finalSolution, n, costMatrix);
    if (finalCost < bestCost) {
        memcpy(bestSolution, finalSolution, (n+1) * sizeof(int));
        bestCost = finalCost;
    }

    // Limpeza
    delete[] twoOptBuffer;
    delete[] buffers.visited;
    delete[] buffers.candidates;
    delete[] buffers.rcl;
    delete[] buffers.routeBuffer;
    
    return bestSolution;
}
