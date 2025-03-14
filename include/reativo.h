#ifndef REATIVO_H
#define REATIVO_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <cstdarg>
#include <ctime>
#include <string>

/**
 * Calcula o custo total de uma rota.
 * @param route Array de inteiros representando a rota (tamanho n+1).
 * @param n Número de cidades.
 * @param costMatrix Matriz de custos (dimensão n x n).
 * @return O custo total da rota.
 */
double calculateCost(int* route, int n, double** costMatrix);

/**
 * Ordena um array de candidatos (índices) com base no custo da aresta do vértice 'current',
 * usando uma ordenação por seleção.
 * @param candidates Array de índices candidatos.
 * @param count Número de candidatos.
 * @param current Índice do vértice atual.
 * @param costMatrix Matriz de custos.
 */
void sortCandidates(int* candidates, int count, int current, double** costMatrix);

/**
 * Constrói uma solução para o TSP utilizando uma abordagem gulosa randomizada com uma
 * Restricted Candidate List (RCL) controlada pelo parâmetro alpha.
 * @param costMatrix Matriz de custos (dimensão n x n).
 * @param n Número de cidades.
 * @param alpha Parâmetro de controle (0 <= alpha <= 1).
 * @return Array de inteiros (tamanho n+1) representando a rota (fechada).
 */
int* greedyRandomizedConstruction(double** costMatrix, int n, double alpha);

/**
 * Aplica a busca local 2‑Opt para melhorar uma solução.
 * @param route Solução inicial (array de tamanho n+1).
 * @param n Número de cidades.
 * @param costMatrix Matriz de custos.
 * @return Nova rota (array de tamanho n+1) com melhoria, se encontrada.
 */
int* twoOpt(int* route, int n, double** costMatrix);

/**
 * Implementa o Reactive GRASP para o TSP, realizando iterações e ajustando
 * dinamicamente o parâmetro alpha com base no desempenho.
 * @param costMatrix Matriz de custos (dimensão n x n).
 * @param n Número de cidades.
 * @param maxIterations Número máximo de iterações.
 * @return A melhor rota encontrada (array de tamanho n+1).
 */
int* reactiveGRASP(double** costMatrix, int n, int maxIterations);

#endif // REATIVO_H
