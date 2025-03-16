#include "listaAdj.h"
#include <iostream>

using namespace std;

// ✅ Construtor padrão (evita erros de inicialização sem argumentos)
ListaAdj::ListaAdj() : lista(nullptr), numVertices(0) {}

// ✅ Construtor correto (inicializa lista de adjacência)
ListaAdj::ListaAdj(int numVertices) : numVertices(numVertices) {
    lista = new NoAdj*[numVertices];
    for (int i = 0; i < numVertices; i++) {
        lista[i] = nullptr;
    }
}

// ✅ Método para inserir uma aresta na lista de adjacência
void ListaAdj::inserirAresta(int origem, int destino, int peso) {
    NoAdj* novo = new NoAdj(destino, peso);
    novo->prox = lista[origem];
    lista[origem] = novo;
}

// ✅ Método para imprimir o grafo
void ListaAdj::imprimir() const {
    for (int i = 0; i < numVertices; i++) {
        cout << "Vertice " << i << ": ";
        NoAdj* atual = lista[i];
        while (atual) {
            cout << " -> " << atual->destino << "(" << atual->peso << ")";
            atual = atual->prox;
        }
        cout << endl;
    }
}

//  Destrutor para liberar memória
ListaAdj::~ListaAdj() {
    for (int i = 0; i < numVertices; i++) {
        NoAdj* atual = lista[i];
        while (atual) {
            NoAdj* temp = atual;
            atual = atual->prox;
            delete temp;
        }
    }
    delete[] lista;
}

int ListaAdj::getCusto(int origem, int destino) const {
    NoAdj* atual = lista[origem]; // Supondo que `lista` seja um array de ponteiros para NoAdj
    while (atual) {
        if (atual->destino == destino) {
            return atual->peso;
        }
        atual = atual->prox;
    }
    return -1; // Retorna -1 se não houver conexão entre os vértices
}

std::pair<int, int>* ListaAdj::obterVizinhos(int vertice, int& tamanho) const {
    tamanho = 0;

    // Conta o número de vizinhos
    NoAdj* atual = lista[vertice];
    while (atual) {
        tamanho++;
        atual = atual->prox;
    }

    // Aloca um array para armazenar os vizinhos
    std::pair<int, int>* vizinhos = new std::pair<int, int>[tamanho];

    // Preenche o array com os vizinhos
    atual = lista[vertice];
    for (int i = 0; i < tamanho; i++) {
        vizinhos[i] = {atual->destino, atual->peso};
        atual = atual->prox;
    }

    return vizinhos;
}

