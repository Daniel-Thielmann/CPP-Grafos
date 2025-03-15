#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#include "listaAdj.h"
#include "grafo.h"

class GrafoLista : public Grafo {
private:
    ListaAdj* listaAdj;  // Lista de adjacência

public:
    GrafoLista(int numVertices, bool direcionado, bool verticesPonderados, bool arestasPonderadas);
    ~GrafoLista();
    
    // Implementações dos métodos virtuais da classe base Grafo
    void adicionarAresta(int origem, int destino, int peso) override;
    void imprimirGrafo() const override;
    void carregarGrafo(const std::string& nomeArquivo) override;
    std::pair<int, int>* getArestas(int vertice, int& tamanho) const override;
};

#endif // GRAFO_LISTA_H