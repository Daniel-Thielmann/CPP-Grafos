#include "grafo_matriz.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>  

using namespace std;

// Construtor otimizado: inicializa a matriz de adjacência de forma compacta
GrafoMatriz::GrafoMatriz(int numVertices, bool direcionado, bool verticesPonderados, bool arestasPonderadas)
    : Grafo(numVertices, direcionado, verticesPonderados, arestasPonderadas), numVertices(numVertices) {

    cout << "[LOG] Inicializando matriz de adjacencia compacta para " << numVertices << " vertices..." << endl;

    clock_t startAlloc = clock();  

    matrizAdj = new int[numVertices * numVertices]();
    
    clock_t endAlloc = clock();
    double tempoAlloc = double(endAlloc - startAlloc) / CLOCKS_PER_SEC;
    cout << "[LOG] Matriz alocada e inicializada em " << tempoAlloc << " segundos." << endl;
}

// Destrutor: libera a memória alocada
GrafoMatriz::~GrafoMatriz() {
    cout << "[LOG] Liberando memoria da matriz de adjacencia..." << endl;
    delete[] matrizAdj;
    cout << "[LOG] Memoria liberada com sucesso!" << endl;
}

// Adiciona uma aresta ao grafo
void GrafoMatriz::adicionarAresta(int origem, int destino, int peso) {
    if (origem < 0 || origem >= numVertices || destino < 0 || destino >= numVertices) {
        cerr << "[ERRO] Índices inválidos na aresta: " << origem << " -> " << destino << endl;
        return;
    }

    int idx = origem * numVertices + destino;
    matrizAdj[idx] = peso;

    if (!ehDirecionado()) {
        matrizAdj[destino * numVertices + origem] = peso;
    }
}

// Imprime a matriz de adjacência
void GrafoMatriz::imprimirGrafo() const {
    cout << "[LOG] Matriz de Adjacencia carregada para " << numVertices << " vertices." << endl;
    
    if (numVertices > 1000) {
        cout << "[LOG] Matriz muito grande. Impressao omitida para evitar travamentos." << endl;
        return;
    }

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            int idx = i * numVertices + j;
            int peso = matrizAdj[idx];
            cout << (peso != 0 ? to_string(peso) : "∞") << "\t";
        }
        cout << endl;
    }
}

// Otimização: Carrega o grafo de forma compacta e exibe progresso a cada 5.000 arestas
void GrafoMatriz::carregarGrafo(const string& nomeArquivo) {
    cout << "[LOG] Iniciando leitura do arquivo: " << nomeArquivo << endl;

    ifstream arquivo(nomeArquivo);
    if (!arquivo) {
        cerr << "[ERRO] Falha ao abrir o arquivo!" << endl;
        return;
    }

    int n, d, vp, ap;
    arquivo >> n >> d >> vp >> ap;
    cout << "[LOG] Arquivo lido com sucesso! Numero de vertices: " << n << endl;

    this->numVertices = n;
    this->direcionado = d;
    this->verticesPonderados = vp;
    this->arestasPonderadas = ap;

    int origem, destino, peso;
    int totalArestas = 0;

    clock_t start = clock();  

    while (arquivo >> origem >> destino >> peso) {
        adicionarAresta(origem - 1, destino - 1, peso);
        totalArestas++;

        // 🔥 Atualiza progresso a cada 5.000 arestas
        if (totalArestas % 5000 == 0) {
            cout << "[LOG] " << totalArestas << " arestas carregadas..." << endl;
        }
    }

    clock_t end = clock();
    double tempoGasto = double(end - start) / CLOCKS_PER_SEC;

    arquivo.close();
    cout << "[LOG] Total de arestas carregadas: " << totalArestas << endl;
    cout << "[LOG] Tempo total de carregamento: " << tempoGasto << " segundos" << endl;
}


// Retorna o peso de uma aresta
    int GrafoMatriz::getPesoAresta(int origem, int destino) const {
    if (origem < 0 || origem >= numVertices || destino < 0 || destino >= numVertices) {
        cerr << "[ERRO] Indice invalido em getPesoAresta(): " << origem << " -> " << destino << endl;
        return -1; // Retornar um valor invalido seguro
    }
    
    int idx = origem * numVertices + destino;
    
    if (!matrizAdj) {
        cerr << "[ERRO] Matriz de Adjacencia nao alocada corretamente!" << endl;
        return -1;
    }

    return matrizAdj[idx];
}


// Retorna a distância entre duas cidades
int GrafoMatriz::obterDistancia(int cidade1, int cidade2) const {
    return getPesoAresta(cidade1, cidade2);
}

// Retorna o número de cidades (vértices)
int GrafoMatriz::obterNumCidades() const {
    return numVertices;
}

// Retorna as arestas de um vértice
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

