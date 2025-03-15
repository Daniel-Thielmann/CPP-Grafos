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
        cout << "Vértice " << i << ": ";
        NoAdj* atual = lista[i];
        while (atual) {
            cout << " -> " << atual->destino << "(" << atual->peso << ")";
            atual = atual->prox;
        }
        cout << endl;
    }
}

// ✅ Destrutor para liberar memória
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
    if (origem < 0 || origem >= numVertices || destino < 0 || destino >= numVertices) {
        return -1; // Retorna -1 se os índices forem inválidos
    }

    NoAdj* atual = lista[origem];
    while (atual) {
        if (atual->destino == destino) {
            return atual->peso; // Retorna o peso da aresta encontrada
        }
        atual = atual->prox;
    }

    return -1; // Retorna -1 se não houver aresta entre origem e destino
}

// Retornar os vizinhos e pesos do vértice especificado
std::pair<int, int>* ListaAdj::obterVizinhos(int vertice, int& tamanho) const {
    if (vertice < 0 || vertice >= numVertices) {
        tamanho = 0;
        return nullptr;
    }

    // Contar número de vizinhos
    int count = 0;
    NoAdj* atual = lista[vertice];
    while (atual) {
        count++;
        atual = atual->prox;
    }

    // Criar array dinâmico
    std::pair<int, int>* vizinhos = new std::pair<int, int>[count];
    tamanho = count;

    // Preencher array com vizinhos e pesos
    atual = lista[vertice];
    for (int i = 0; i < count; i++) {
        vizinhos[i] = {atual->destino, atual->peso};
        atual = atual->prox;
    }

    return vizinhos;
}