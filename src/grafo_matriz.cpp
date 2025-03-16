#include "grafo_matriz.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <ctime>

using namespace std;

// Construtor: inicializa a matriz com alocação dinâmica somente quando necessário
GrafoMatriz::GrafoMatriz(int numVertices, bool direcionado, bool verticesPonderados, bool arestasPonderadas)
    : Grafo(numVertices, direcionado, verticesPonderados, arestasPonderadas), numVertices(numVertices) {
    
    cout << "[LOG] Inicializando matriz dinâmica para " << numVertices << " vértices..." << endl;

    matrizAdj = new int*[numVertices];
    for (int i = 0; i < numVertices; i++) {
        matrizAdj[i] = nullptr; // Inicialmente, nenhuma linha é alocada
    }

    cout << "[LOG] Matriz alocada de forma eficiente!" << endl;
}

// Destrutor: libera a matriz da memória
GrafoMatriz::~GrafoMatriz() {
    cout << "[LOG] Liberando memória da matriz de adjacência..." << endl;
    for (int i = 0; i < numVertices; i++) {
        delete[] matrizAdj[i];  // Libera apenas as linhas alocadas
    }
    delete[] matrizAdj;
    cout << "[LOG] Memória liberada com sucesso!" << endl;
}

// Adiciona aresta ao grafo
void GrafoMatriz::adicionarAresta(int origem, int destino, int peso) {
    if (!matrizAdj[origem]) {
        matrizAdj[origem] = new int[numVertices]; // Aloca linha apenas quando necessário
        for (int j = 0; j < numVertices; j++) matrizAdj[origem][j] = -1; // Inicializa com -1
    }
    matrizAdj[origem][destino] = peso;
    
    if (!ehDirecionado()) {
        if (!matrizAdj[destino]) {
            matrizAdj[destino] = new int[numVertices];
            for (int j = 0; j < numVertices; j++) matrizAdj[destino][j] = -1;
        }
        matrizAdj[destino][origem] = peso;
    }
}

// Imprime a matriz de adjacência (somente elementos válidos)
void GrafoMatriz::imprimirGrafo() const {
    cout << "[LOG] Imprimindo matriz de adjacência:" << endl;
    for (int i = 0; i < numVertices; i++) {
        if (matrizAdj[i]) {
            for (int j = 0; j < numVertices; j++) {
                int peso = matrizAdj[i][j];
                cout << (peso == -1 ? "∞" : to_string(peso)) << "\t";
            }
            cout << endl;
        }
    }
}

// Carrega o grafo a partir de um arquivo
void GrafoMatriz::carregarGrafo(const string& nomeArquivo) {
    cout << "[LOG] Iniciando leitura do arquivo: " << nomeArquivo << endl;

    ifstream arquivo(nomeArquivo);
    if (!arquivo) {
        cerr << "[ERRO] Falha ao abrir o arquivo!" << endl;
        return;
    }

    int n, d, vp, ap;
    arquivo >> n >> d >> vp >> ap;
    cout << "[LOG] Arquivo lido com sucesso! Número de vértices: " << n << endl;
    
    this->numVertices = n;
    this->direcionado = d;
    this->verticesPonderados = vp;
    this->arestasPonderadas = ap;

    int origem, destino, peso;
    int totalArestas = 0;

    while (arquivo >> origem >> destino >> peso) {
        adicionarAresta(origem - 1, destino - 1, peso);
        totalArestas++;

        // Atualiza log a cada 10% das arestas processadas
        if (totalArestas % (numVertices / 10) == 0) {
            cout << "[LOG] " << (totalArestas * 100 / numVertices) << "% do arquivo processado..." << endl;
        }
    }

    arquivo.close();
    cout << "[LOG] Total de arestas carregadas: " << totalArestas << endl;
}

// Retorna as arestas do vértice como um vetor alocado dinamicamente
std::pair<int, int>* GrafoMatriz::getArestas(int vertice, int& tamanho) const {
    if (vertice < 0 || vertice >= numVertices || !matrizAdj[vertice]) {
        tamanho = 0;
        return nullptr;
    }

    tamanho = 0;
    for (int j = 0; j < numVertices; j++) {
        if (matrizAdj[vertice][j] != -1) {
            tamanho++;
        }
    }

    std::pair<int, int>* vizinhos = new std::pair<int, int>[tamanho];
    int index = 0;
    for (int j = 0; j < numVertices; j++) {
        int peso = matrizAdj[vertice][j];
        if (peso != -1) {
            vizinhos[index++] = {j, peso};
        }
    }

    return vizinhos;
}

// Retorna peso da aresta (ou infinito se não existir)
int GrafoMatriz::getPesoAresta(int origem, int destino) const {
    return (matrizAdj[origem] ? matrizAdj[origem][destino] : -1);
}

int GrafoMatriz::obterDistancia (int cidade1, int cidade2) const{
    return matrizAdj[cidade1][cidade2];
}
