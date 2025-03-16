#include "grafo_lista.h"
#include <fstream>
#include <iostream>

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
        // Processamento manual da linha
        int origem = 0, destino = 0, peso = 0;
        size_t posInicio = 0;
        size_t posFim = linha.find(' ', posInicio); // Encontra o primeiro espaço

        // Extrai a origem
        if (posFim != std::string::npos) {
            origem = std::stoi(linha.substr(posInicio, posFim - posInicio));
            posInicio = posFim + 1; // Avança para o próximo número
            posFim = linha.find(' ', posInicio); // Encontra o próximo espaço
        }

        // Extrai o destino
        if (posFim != std::string::npos) {
            destino = std::stoi(linha.substr(posInicio, posFim - posInicio));
            posInicio = posFim + 1; // Avança para o próximo número
        }

        // Extrai o peso (último número da linha)
        if (posInicio < linha.size()) {
            peso = std::stoi(linha.substr(posInicio));
        }

        // Adiciona a aresta ao grafo
        adicionarAresta(origem, destino, peso);
    }
}

std::pair<int, int>* GrafoLista::getArestas(int vertice, int& tamanho) const {
    return listaAdj->obterVizinhos(vertice, tamanho);
}

const ListaAdj& GrafoLista::getListaAdj() const {
    return *listaAdj; // Supondo que listaAdj seja um ponteiro para a lista de adjacência
}
int GrafoLista::obterDistancia (int cidade1, int cidade2) const{
    return cidade1 - cidade2;
}
