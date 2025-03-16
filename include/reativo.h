// reativo.h
#ifndef REATIVO_H
#define REATIVO_H

const double INF = 1e9;

// Estrutura para armazenar buffers reutilizáveis
struct GRASPBuffers {
    bool* visited;
    int* candidates;
    int* rcl;
    int* routeBuffer;
};

// Protótipos otimizados
double calculateCost(int* route, int n, double** costMatrix);
void sortCandidates(int* candidates, int count, int current, double** costMatrix);
int* greedyRandomizedConstruction(double** costMatrix, int n, double alpha, GRASPBuffers& buffers);
int* twoOpt(int* route, int n, double** costMatrix, int* buffer);
int* reactiveGRASP(double** costMatrix, int n, int maxIterations);

#endif // REATIVO_H