#ifndef REATIVO_H
#define REATIVO_H

const double INF = 1e9;

double calculateCost(int* route, int n, double** costMatrix);
void sortCandidates(int* candidates, int count, int current, double** costMatrix);
int* greedyRandomizedConstruction(double** costMatrix, int n, double alpha);
int* twoOpt(int* route, int n, double** costMatrix);
int* reactiveGRASP(double** costMatrix, int n, int maxIterations);

#endif // REATIVO_H
