#include "grafo_lista.h"
#include <fstream>
#include <iostream>

// Construtor corrigido
GrafoLista::GrafoLista(int numVertices, bool direcionado, bool verticesPonderados, bool arestasPonderadas)
    : Grafo(numVertices, direcionado, verticesPonderados, arestasPonderadas),
      listaAdj(numVertices) {} // Inicializa a lista corretamente

// Método para adicionar aresta
void GrafoLista::adicionarAresta(int origem, int destino, int peso) {
    listaAdj.inserirAresta(origem, destino, peso);
    if (!ehDirecionado()) {
        listaAdj.inserirAresta(destino, origem, peso);
    }
}

// Método para imprimir
void GrafoLista::imprimirGrafo() const {
    std::cout << "Lista de Adjacência:" << std::endl;
    listaAdj.imprimir();
}

// Método para carregar do arquivo
void GrafoLista::carregarGrafo(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return;
    }

    int n, d, vp, ap;
    arquivo >> n >> d >> vp >> ap;
    
    // Reinicializa o grafo
    this->numVertices = n;
    this->direcionado = d;
    this->verticesPonderados = vp;
    this->arestasPonderadas = ap;
    listaAdj = ListaAdj(n); // Recria a lista

    int origem, destino, peso;
    while (arquivo >> origem >> destino >> peso) {
        adicionarAresta(origem - 1, destino - 1, peso);
    }
    arquivo.close();
}