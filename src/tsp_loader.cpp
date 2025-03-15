#include "tsp_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void TSPLoader::carregarTSP(
    const std::string& nomeArquivo, 
    GrafoMatriz* &grafoMatriz, 
    GrafoLista* &grafoLista
) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo: " << nomeArquivo << endl;
        return;
    }

    string linha;
    int numVertices = 0;
    vector<pair<double, double>> coordenadas;

    // Lendo o cabeçalho do arquivo TSP
    while (getline(arquivo, linha)) {
        if (linha.find("DIMENSION") != string::npos) {
            stringstream ss(linha);
            string lixo;
            ss >> lixo >> lixo >> numVertices;  // Corrigido para pegar o número de vértices corretamente
        } else if (linha.find("NODE_COORD_SECTION") != string::npos) {
            break; // Início dos dados de coordenadas
        }
    }

    if (numVertices == 0) {
        cerr << "Erro: DIMENSION não encontrada no arquivo " << nomeArquivo << endl;
        return;
    }

    // Lendo as coordenadas dos vértices
    for (int i = 0; i < numVertices; i++) {
        int id;
        double x, y;
        if (!(arquivo >> id >> x >> y)) {
            cerr << "Erro ao ler as coordenadas do vértice " << i + 1 << endl;
            return;
        }
        coordenadas.push_back({x, y});
    }

    // Criar os grafos
    grafoMatriz = new GrafoMatriz(numVertices, false, false, true);
    grafoLista = new GrafoLista(numVertices, false, false, true);

    cout << "🔹 Criando as arestas a partir da distância Euclidiana..." << endl;

    // Criando as arestas com base na distância euclidiana
    for (int i = 0; i < numVertices; i++) {
        for (int j = i + 1; j < numVertices; j++) {
            double dx = coordenadas[i].first - coordenadas[j].first;
            double dy = coordenadas[i].second - coordenadas[j].second;
            int distancia = static_cast<int>(round(sqrt(dx * dx + dy * dy)));

            grafoMatriz->adicionarAresta(i, j, distancia);
            grafoLista->adicionarAresta(i, j, distancia);
            grafoMatriz->adicionarAresta(j, i, distancia);
            grafoLista->adicionarAresta(j, i, distancia);
        }
    }

    arquivo.close();
    cout << "✅ Dados carregados com sucesso a partir de " << nomeArquivo << endl;
    cout << "Total de vértices: " << numVertices << endl;
}
