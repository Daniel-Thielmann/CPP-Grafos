#include "guloso.h"
#include <iostream>
#include <fstream>

vector<int> Guloso::resolverTSP(const GrafoMatriz& grafo) {
    int numVertices = grafo.getMatrizAdj().size();
    vector<int> melhorCaminho;
    int menorCusto = numeric_limits<int>::max();
    
    // Testa todos os vértices como ponto inicial
    for (int verticeInicial = 0; verticeInicial < numVertices; verticeInicial++) {
        vector<bool> visitado(numVertices, false);
        vector<int> caminho;
        int atual = verticeInicial;
        int custoTotal = 0;
        
        caminho.push_back(atual);
        visitado[atual] = true;
        
        for (int i = 1; i < numVertices; i++) {
            int proximo = -1;
            int menorDistancia = numeric_limits<int>::max();
            
            for (int j = 0; j < numVertices; j++) {
                if (!visitado[j] && grafo.getMatrizAdj()[atual][j] > 0 && grafo.getMatrizAdj()[atual][j] < menorDistancia) {
                    menorDistancia = grafo.getMatrizAdj()[atual][j];
                    proximo = j;
                }
            }
            
            if (proximo == -1) break; // Evita erro em grafos desconexos
            
            caminho.push_back(proximo);
            visitado[proximo] = true;
            custoTotal += menorDistancia;
            atual = proximo;
        }
        
        // Retorna à cidade inicial
        if (grafo.getMatrizAdj()[atual][verticeInicial] > 0) {
            caminho.push_back(verticeInicial);
            custoTotal += grafo.getMatrizAdj()[atual][verticeInicial];
        }
        
        // Atualiza o melhor caminho
        if (custoTotal < menorCusto) {
            menorCusto = custoTotal;
            melhorCaminho = caminho;
        }
    }
    
    cout << "Melhor ciclo Hamiltoniano encontrado: ";
    for (int cidade : melhorCaminho) {
        cout << cidade << " ";
    }
    cout << "\nCusto Total: " << menorCusto << endl;
    
    return melhorCaminho;
}