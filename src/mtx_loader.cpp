#include "mtx_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>

void MTXLoader::carregarMTX(
    const std::string& nomeArquivo, 
    GrafoMatriz* &grafoMatriz, 
    GrafoLista* &grafoLista
) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo) {
        std::cerr << "❌ Erro ao abrir o arquivo: " << nomeArquivo << std::endl;
        return;
    }

    std::string linha;
    bool primeiraLinha = true;
    int numVertices, numArestas;
    bool direcionado = false;

    while (std::getline(arquivo, linha)) {
        if (linha[0] == '%') {
            if (linha.find("symmetric") != std::string::npos) direcionado = false;
            continue;
        }

        if (primeiraLinha) {
            std::stringstream ss(linha);
            ss >> numVertices >> numVertices >> numArestas;
            
            // Criar grafos com base nas informações lidas
            grafoMatriz = new GrafoMatriz(numVertices, direcionado, false, true);
            grafoLista = new GrafoLista(numVertices, direcionado, false, true);
            
            std::cout << "🔹 Grafos criados: " << numVertices << " vértices, " 
                      << numArestas << " arestas" << std::endl;
            primeiraLinha = false;
            continue;
        }

        int origem, destino, peso;
        std::stringstream ss(linha);
        ss >> origem >> destino >> peso;

        // Ajustar índices para zero-based
        origem--; destino--;

        // Adicionar aresta a ambos os grafos
        grafoMatriz->adicionarAresta(origem, destino, peso);
        grafoLista->adicionarAresta(origem, destino, peso);

        if (!direcionado) {
            grafoMatriz->adicionarAresta(destino, origem, peso);
            grafoLista->adicionarAresta(destino, origem, peso);
        }
    }

    arquivo.close();
    std::cout << "✅ Dados carregados em ambos os grafos com sucesso!" << std::endl;
}