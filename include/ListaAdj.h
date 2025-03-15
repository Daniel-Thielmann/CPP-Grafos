#ifndef LISTA_ADJ_H
#define LISTA_ADJ_H

#include <iostream>

struct NoAdj {
    int destino;
    int peso;
    NoAdj* prox;
    NoAdj(int d, int p) : destino(d), peso(p), prox(nullptr) {}
};

class ListaAdj {

    private:
    
        NoAdj** lista;
        int numVertices;
    
    public:

   


        ListaAdj();
        ListaAdj(int numVertices);
        void inserirAresta(int origem, int destino, int peso);
        void imprimir() const;
        int getCusto(int origem, int destino) const; // Novo método
        ~ListaAdj();
    };

#endif // LISTA_ADJ_H
