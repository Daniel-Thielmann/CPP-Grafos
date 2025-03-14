#include "grafo_lista.h"
#include <iostream>
#include <fstream>
#include <sstream>

GrafoLista::GrafoLista(int numVertices, bool direcionado, bool verticesPonderados, bool arestasPonderadas)
    : Grafo(numVertices, direcionado, verticesPonderados, arestasPonderadas)
{
    listaAdj = new ListaAdj(numVertices);
}

GrafoLista::~GrafoLista() {
    delete listaAdj;
}

void GrafoLista::adicionarAresta(int origem, int destino, int peso) {
    listaAdj->inserirAresta(origem, destino, peso);
    if (!ehDirecionado()) {
        listaAdj->inserirAresta(destino, origem, peso);
    }
}

void GrafoLista::imprimirGrafo() const {
    std::cout << "Imprimindo grafo:\n";
    listaAdj->imprimir();
}

void GrafoLista::carregarGrafo(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::istringstream iss(linha);
        int origem, destino, peso;
        iss >> origem >> destino >> peso;
        adicionarAresta(origem, destino, peso);
    }
}

std::pair<int, int>* GrafoLista::getArestas(int vertice, int& tamanho) const {
    return listaAdj->obterVizinhos(vertice, tamanho);
}