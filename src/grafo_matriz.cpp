#include "grafo_matriz.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>  // Para memset

using namespace std;

// Construtor: inicializa a matriz de adjacência de forma otimizada
GrafoMatriz::GrafoMatriz(int numVertices, bool direcionado, bool verticesPonderados, bool arestasPonderadas)
    : Grafo(numVertices, direcionado, verticesPonderados, arestasPonderadas), numVertices(numVertices) {

    cout << "[LOG] Inicializando matriz de adjacência para " << numVertices << " vértices..." << endl;

    // Aloca matriz unidimensional e bitmap de cache
    matrizAdj = new int[numVertices * numVertices];
    cacheArestas = new bool[numVertices * numVertices];

    // Inicializa com -1 e falso no cache
    memset(matrizAdj, -1, numVertices * numVertices * sizeof(int));
    memset(cacheArestas, false, numVertices * numVertices * sizeof(bool));

    cout << "[LOG] Matriz e cache inicializados!" << endl;
}

// Destrutor: libera a memória alocada para a matriz
GrafoMatriz::~GrafoMatriz() {
    cout << "[LOG] Liberando memória da matriz de adjacência..." << endl;
    delete[] matrizAdj;
    delete[] cacheArestas;
    cout << "[LOG] Memória liberada com sucesso!" << endl;
}

// Adiciona uma aresta ao grafo
void GrafoMatriz::adicionarAresta(int origem, int destino, int peso) {
    if (origem < 0 || origem >= numVertices || destino < 0 || destino >= numVertices) {
        cerr << "[ERRO] Vértices fora do intervalo!" << endl;
        return;
    }

    int idx = origem * numVertices + destino;
    matrizAdj[idx] = peso;
    cacheArestas[idx] = true;

    if (!ehDirecionado()) {
        idx = destino * numVertices + origem;
        matrizAdj[idx] = peso;
        cacheArestas[idx] = true;
    }
}

// Imprime a matriz de adjacência
void GrafoMatriz::imprimirGrafo() const {
    cout << "[LOG] Imprimindo matriz de adjacência:" << endl;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            int idx = i * numVertices + j;
            int peso = matrizAdj[idx];
            cout << (cacheArestas[idx] ? to_string(peso) : "∞") << "\t";
        }
        cout << endl;
    }
}

// Carrega o grafo a partir de um arquivo com otimização máxima
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
    long totalBytes = arquivo.seekg(0, ios::end).tellg();
    arquivo.seekg(0, ios::beg);
    long bytesLidos = arquivo.tellg();
    int progresso = 0;

    clock_t start = clock();  // Inicia medição de tempo

    while (arquivo >> origem >> destino >> peso) {
        adicionarAresta(origem - 1, destino - 1, peso);
        totalArestas++;

        // Atualiza progresso a cada 1%
        bytesLidos = arquivo.tellg();
        int novoProgresso = (bytesLidos * 100) / totalBytes;
        if (novoProgresso > progresso) {
            progresso = novoProgresso;
            cout << "[LOG] " << progresso << "% do arquivo processado..." << endl;
        }
    }

    clock_t end = clock();  // Finaliza medição de tempo
    double tempoGasto = double(end - start) / CLOCKS_PER_SEC;

    arquivo.close();
    cout << "[LOG] Total de arestas carregadas: " << totalArestas << endl;
    cout << "[LOG] Tempo total de carregamento: " << tempoGasto << " segundos" << endl;
}

// Retorna o peso de uma aresta
int GrafoMatriz::getPesoAresta(int origem, int destino) const {
    int idx = origem * numVertices + destino;
    return cacheArestas[idx] ? matrizAdj[idx] : -1;
}

// Retorna a distância entre duas cidades
int GrafoMatriz::obterDistancia(int cidade1, int cidade2) const {
    return getPesoAresta(cidade1, cidade2);
}

// Retorna o número de cidades (vértices)
int GrafoMatriz::obterNumCidades() const {
    return numVertices;
}

std::pair<int, int>* GrafoMatriz::getArestas(int vertice, int& tamanho) const {
    if (vertice < 0 || vertice >= numVertices) {
        tamanho = 0;
        return nullptr;
    }

    // Contar número de vizinhos
    tamanho = 0;
    for (int j = 0; j < numVertices; j++) {
        if (matrizAdj[vertice * numVertices + j] != -1) {
            tamanho++;
        }
    }

    // Criar um array dinâmico de pares (vértice, peso)
    std::pair<int, int>* vizinhos = new std::pair<int, int>[tamanho];
    int index = 0;
    for (int j = 0; j < numVertices; j++) {
        int peso = matrizAdj[vertice * numVertices + j];
        if (peso != -1) {
            vizinhos[index++] = {j, peso};
        }
    }

    return vizinhos;
}
