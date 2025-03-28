#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Grafo {
protected:
    int numVertices;
    bool direcionado;
    bool verticesPonderados;
    bool arestasPonderadas;

    int numCidades;       // Número de cidades no grafo
    int** matrizAdj;      // Matriz de adjacência para armazenar as distâncias (array bidimensional)

public:
    // Construtor e destrutor virtual
    Grafo(int numVertices, bool direcionado, bool verticesPonderados, bool arestasPonderadas);
    virtual ~Grafo() {}

    // Métodos virtuais puros (serão implementados nas classes derivadas)
    virtual void adicionarAresta(int origem, int destino, int peso) = 0;
    virtual void imprimirGrafo() const = 0;
    virtual void carregarGrafo(const string& nomeArquivo) = 0;
    virtual std::pair<int, int>* getArestas(int vertice, int& tamanho) const = 0;

    // Métodos auxiliares
    int getNumVertices() const;
    bool ehDirecionado() const;
    bool temVerticesPonderados() const;
    bool temArestasPonderadas() const;


     //Metodo do Randomizado
     /*Grafo(const std::string& nomeArquivo); // Construtor para ler instâncias de arquivo
    //~Grafo();  */                            // Destrutor para liberar memória alocada
    //void adicionarAresta(int cidade1, int cidade2, int distancia);
    virtual int obterDistancia(int cidade1, int cidade2 ) const = 0;
    int obterNumCidades() const;
    //int obterNumCidades() const;*/
};

#endif // GRAFO_H