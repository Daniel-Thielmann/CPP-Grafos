#include "grafo_lista.h"
#include <iostream>
#include <fstream>

using namespace std;

// ✅ Construtor corrigido para evitar erro de inicialização
GrafoLista::GrafoLista(int numVertices, bool direcionado, bool verticesPonderados, bool arestasPonderadas)
    : Grafo(numVertices, direcionado, verticesPonderados, arestasPonderadas) {
    listaAdj = new ListaAdj[numVertices];
    for (int i = 0; i < numVertices; i++) {
        listaAdj[i] = ListaAdj(numVertices);
    }
}

// ✅ Destrutor para liberar memória corretamente
GrafoLista::~GrafoLista() {
    delete[] listaAdj;
}

// ✅ Método para adicionar aresta corretamente
void GrafoLista::adicionarAresta(int origem, int destino, int peso) {
    listaAdj[origem].inserirAresta(origem, destino, peso);
    if (!ehDirecionado()) {
        listaAdj[destino].inserirAresta(destino, origem, peso);
    }
}

// ✅ Método para imprimir a lista de adjacência
void GrafoLista::imprimirGrafo() const {
    cout << "Lista de Adjacência:" << endl;
    for (int i = 0; i < numVertices; i++) {
        listaAdj[i].imprimir();
    }
}

// ✅ Método para carregar o grafo de um arquivo
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
    for (int i = 0; i < n; i++) {
        listaAdj[i] = ListaAdj(n);
    }

    int origem, destino, peso;
    while (arquivo >> origem >> destino >> peso) {
        adicionarAresta(origem - 1, destino - 1, peso); // Ajustando índices para zero-based
    }
    arquivo.close();
}
