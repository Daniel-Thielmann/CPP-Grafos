// ListaAdj.h
#ifndef LISTA_ADJ_H
#define LISTA_ADJ_H

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
    int** costMatrix; // Cache da matriz de custos

    void buildCostMatrix() {
        costMatrix = new int*[numVertices];
        for (int i = 0; i < numVertices; ++i) {
            costMatrix[i] = new int[numVertices];
            for (int j = 0; j < numVertices; ++j) {
                costMatrix[i][j] = -1;
            }
            NoAdj* atual = lista[i];
            while (atual) {
                costMatrix[i][atual->destino] = atual->peso;
                atual = atual->prox;
            }
        }
    }

public:
    ListaAdj();
    explicit ListaAdj(int numVertices);
    ~ListaAdj();
    
    void inserirAresta(int origem, int destino, int peso);
    int getCusto(int origem, int destino) const;
    void imprimir() const;
};

#endif // LISTA_ADJ_H