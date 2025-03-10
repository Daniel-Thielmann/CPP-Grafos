#include <iostream>
#include "./include/mtx_loader.h"
#include "./include/ListaAdj.h"

using namespace std;

int main() {
    cout << "Iniciando o programa!" << endl;

    string arquivo = "entradas/instancias/road-usroads.mtx";
    cout << "Tentando carregar o arquivo: " << arquivo << endl;

    int numVertices, numArestas;
    ListaAdj* listaAdj = nullptr;

    MTXLoader::carregarMTX(arquivo, numVertices, numArestas, listaAdj);

    if (!listaAdj) {
        cerr << "Erro ao carregar instância!" << endl;
        return 1;
    }

    cout << "Arquivo carregado com sucesso! " << numVertices << " vértices e " << numArestas << " arestas." << endl;

    // Teste: imprimir as 5 primeiras listas de adjacência
    listaAdj->imprimir();

    delete listaAdj; // Liberar memória
    cout << "Programa finalizado com sucesso!" << endl;
    return 0;
}
