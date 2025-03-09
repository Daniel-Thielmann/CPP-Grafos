#include "ListaAdj.h"
using namespace std;

// Construtor: inicializa um vetor de listas encadeadas
ListaAdj::ListaAdj(int numVertices) {
    this->numVertices = numVertices;
    lista = new NoAdj*[numVertices];
    for (int i = 0; i < numVertices; i++) {
        lista[i] = nullptr; // Inicializa lista vazia para cada vértice
    }
}

// Destrutor: libera memória das listas encadeadas
ListaAdj::~ListaAdj() {
    for (int i = 0; i < numVertices; i++) {
        NoAdj* atual = lista[i];
        while (atual) {
            NoAdj* prox = atual->prox;
            delete atual;
            atual = prox;
        }
    }
    delete[] lista;
}

// Insere uma aresta na lista de adjacência
void ListaAdj::inserirAresta(int origem, int destino, int peso) {
    NoAdj* novo = new NoAdj(destino, peso);
    novo->prox = lista[origem];
    lista[origem] = novo;

    // Como o grafo é não direcionado, adicionamos a aresta oposta também
    NoAdj* novo2 = new NoAdj(origem, peso);
    novo2->prox = lista[destino];
    lista[destino] = novo2;
}

// Imprime a lista de adjacência
void ListaAdj::imprimir() const {
    for (int i = 0; i < numVertices; i++) {
        cout << "Vértice " << i + 1 << ": ";
        NoAdj* atual = lista[i];
        while (atual) {
            cout << " -> (" << atual->destino + 1 << ", " << atual->peso << ")";
            atual = atual->prox;
        }
        cout << endl;
    }
}
