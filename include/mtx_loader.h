#ifndef MTX_LOADER_H
#define MTX_LOADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ListaAdj.h"

using namespace std;

class MTXLoader {
public:
    static void carregarMTX(const string& nomeArquivo, int &numVertices, int &numArestas, ListaAdj* &listaAdj);
};

#endif // MTX_LOADER_H
