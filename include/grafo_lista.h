#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#include "grafo.h"
#include "ListaAdj.h"

class GrafoLista : public Grafo {
private:
    ListaAdj* listaAdj; // Vetor de listas encadeadas

public:
    GrafoLista(int numVertices, bool direcionado, bool verticesPonderados, bool arestasPonderadas);
    ~GrafoLista();

    void adicionarAresta(int origem, int destino, int peso) override;
    void imprimirGrafo() const override;
    void carregarGrafo(const string& nomeArquivo) override;
};

#endif // GRAFO_LISTA_H
