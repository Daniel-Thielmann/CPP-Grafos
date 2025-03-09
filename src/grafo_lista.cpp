#include "grafo_lista.h"
#include <iostream>
#include <fstream>

using namespace std;

// Construtor: inicializa um vetor de listas encadeadas
GrafoLista::GrafoLista(int numVertices, bool direcionado, bool verticesPonderados, bool arestasPonderadas)
    : Grafo(numVertices, direcionado, verticesPonderados, arestasPonderadas) {
    listaAdj = new ListaAdj[numVertices]; // Aloca um array de listas encadeadas
}

// Destrutor: libera memória
GrafoLista::~GrafoLista() {
    delete[] listaAdj;
}

// Adiciona aresta ao grafo
void GrafoLista::adicionarAresta(int origem, int destino, int peso) {
    listaAdj[origem].inserir(destino, peso);
    if (!ehDirecionado()) {
        listaAdj[destino].inserir(origem, peso);
    }
}

// Imprime a lista de adjacência
void GrafoLista::imprimirGrafo() const {
    cout << "Lista de Adjacência:" << endl;
    for (int i = 0; i < numVertices; i++) {
        listaAdj[i].imprimir(i);
    }
}

// Carrega o grafo de um arquivo
void GrafoLista::carregarGrafo(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    int n, d, vp, ap;
    arquivo >> n >> d >> vp >> ap;
    this->numVertices = n;
    this->direcionado = d;
    this->verticesPonderados = vp;
    this->arestasPonderadas = ap;

    delete[] listaAdj; // Liberar memória antes de realocar
    listaAdj = new ListaAdj[n];

    int origem, destino, peso;
    while (arquivo >> origem >> destino >> peso) {
        adicionarAresta(origem - 1, destino - 1, peso); // Ajustando índices para zero-based
    }
    arquivo.close();
}
