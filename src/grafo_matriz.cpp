#include "grafo_matriz.h"

// Construtor: inicializa a matriz de adjacência
GrafoMatriz::GrafoMatriz(int numVertices, bool direcionado, bool verticesPonderados, bool arestasPonderadas)
    : Grafo(numVertices, direcionado, verticesPonderados, arestasPonderadas) {
    matrizAdj.resize(numVertices, vector<int>(numVertices, -1)); // Inicializa matriz com -1 (sem aresta)
}

// Adiciona aresta ao grafo
void GrafoMatriz::adicionarAresta(int origem, int destino, int peso) {
    matrizAdj[origem][destino] = peso;
    if (!ehDirecionado()) {
        matrizAdj[destino][origem] = peso;
    }
}

// Imprime a matriz de adjacência
void GrafoMatriz::imprimirGrafo() const {
    cout << "Matriz de Adjacência:" << endl;
    for (const auto& linha : matrizAdj) {
        for (int peso : linha) {
            cout << (peso == -1 ? "∞" : to_string(peso)) << "\t";
        }
        cout << endl;
    }
}

// Carrega o grafo a partir de um arquivo
void GrafoMatriz::carregarGrafo(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return;
    }

    int n, d, vp, ap;
    arquivo >> n >> d >> vp >> ap;
    this->numVertices = n;
    this->direcionado = d;
    this->verticesPonderados = vp;
    this->arestasPonderadas = ap;
    matrizAdj.assign(n, vector<int>(n, -1));

    int origem, destino, peso;
    while (arquivo >> origem >> destino >> peso) {
        adicionarAresta(origem - 1, destino - 1, peso); // Ajustando índices para zero-based
    }
    arquivo.close();
}

pair<int, int>* GrafoMatriz::getArestas(int vertice, int& tamanho) const {
    // Usando size_t para a comparação com matrizAdj.size()
    if (vertice < 0 || static_cast<size_t>(vertice) >= matrizAdj.size()) {
        tamanho = 0;
        return nullptr;
    }

    // Contar o número de vizinhos
    size_t count = 0;
    for (size_t i = 0; i < matrizAdj.size(); i++) {
        if (matrizAdj[vertice][i] != 0) {
            count++;
        }
    }

    // Criar array dinâmico
    pair<int, int>* vizinhos = new pair<int, int>[count];
    tamanho = count;

    // Preencher o array com vizinhos e pesos
    size_t index = 0;
    for (size_t i = 0; i < matrizAdj.size(); i++) {
        if (matrizAdj[vertice][i] != 0) {
            vizinhos[index++] = {i, matrizAdj[vertice][i]};
        }
    }

    return vizinhos;
}