#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#include "grafo.h"
#include "ListaAdj.h"

class GrafoLista : public Grafo {
private:
    ListaAdj listaAdj; // Agora é um único objeto (não um array)

public:
    GrafoLista(int numVertices, bool direcionado, bool verticesPonderados, bool arestasPonderadas);
    ~GrafoLista() {}

    void adicionarAresta(int origem, int destino, int peso) override;
    void imprimirGrafo() const override;
    void carregarGrafo(const std::string& nomeArquivo) override;
    int getNumVertices() const { return numVertices; }
    const ListaAdj& getListaAdj() const { return listaAdj; } // Adicione esta linha
   // ListaAdj& getListaAdj() { return listaAdj; } // Mantenha a versão não-const se necessário
};

#endif // GRAFO_LISTA_H