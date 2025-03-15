#ifndef TSP_LOADER_H
#define TSP_LOADER_H

#include "grafo_matriz.h"
#include "grafo_lista.h"
#include <string>

class TSPLoader {
public:
    static void carregarTSP(
        const std::string& nomeArquivo, 
        GrafoMatriz* &grafoMatriz, 
        GrafoLista* &grafoLista
    );
};

#endif // TSP_LOADER_H
