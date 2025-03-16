#include "tsp_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void TSPLoader::carregarTSP(const std::string& nomeArquivo, GrafoMatriz*& grafoMatriz, GrafoLista*& grafoLista) {
    cout << "Iniciando leitura do arquivo: " << nomeArquivo << endl;
    
    ifstream arquivo(nomeArquivo);
    if (!arquivo) {
        cerr << "[ERRO] Falha ao abrir o arquivo!" << endl;
        return;
    }

    string linha;
    int numVertices = 0;

    // Ler as linhas até encontrar DIMENSION
    while (getline(arquivo, linha)) {
        cout << "Linha lida: " << linha << endl;
        
        if (linha.find("DIMENSION") != string::npos) {
            size_t pos = linha.find(":");
            if (pos != string::npos) {
                numVertices = stoi(linha.substr(pos + 1));
            } else {
                cerr << "[ERRO] Formato invalido para DIMENSION." << endl;
                return;
            }
            cout << "Numero de vertices: " << numVertices << " da instancia: " << nomeArquivo << endl;
        } 
        else if (linha.find("NODE_COORD_SECTION") != string::npos) {
            cout << "Iniciando leitura da secao NODE_COORD_SECTION." << endl;
            break;  // Sai do loop para processar as coordenadas
        }
    }

    if (numVertices <= 0) {
        cerr << "[ERRO] Numero de vertices invalido." << endl;
        return;
    }

    // Criar os grafos
    grafoMatriz = new GrafoMatriz(numVertices, false, false, true);
    grafoLista = new GrafoLista(numVertices, false, false, true);

    cout << "Criando as arestas a partir da distancia Euclidiana..." << endl;
    
    int id;
    double x, y;
    vector<pair<double, double>> coordenadas;
    
    for (int i = 0; i < numVertices; i++) {
        if (!(arquivo >> id >> x >> y)) {
            cerr << "[ERRO] Falha ao ler as coordenadas dos vertices." << endl;
            return;
        }
        coordenadas.push_back({x, y});
        cout << "Vertice " << id << ": (" << x << ", " << y << ")" << endl;
    }

    // Criando as arestas com base na distância Euclidiana
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

    cout << "Dados carregados com sucesso a partir de " << nomeArquivo << endl;
}
