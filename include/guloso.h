#ifndef GULOSO_H
#define GULOSO_H

#include "grafo_matriz.h"
#include <vector>
#include <limits>
#include <iostream>

using namespace std;

class Guloso {
public:
    static vector<int> resolverTSP(const GrafoMatriz& grafo);
};

#endif // GULOSO_H