#ifndef MTX_LOADER_H
#define MTX_LOADER_H

#include "grafo_matriz.h"
#include "grafo_lista.h"
#include <string>

class MTXLoader {
public:
    static void carregarMTX(
        const std::string& nomeArquivo, 
        GrafoMatriz* &grafoMatriz, 
        GrafoLista* &grafoLista
    );
};

#endif // MTX_LOADER_H