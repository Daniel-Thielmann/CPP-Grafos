#include "mtx_loader.h"

void MTXLoader::carregarMTX(const string& nomeArquivo, int &numVertices, int &numArestas, ListaAdj* &listaAdj) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo) {
        cerr << "❌ Erro ao abrir o arquivo: " << nomeArquivo << endl;
        return;
    }

    string linha;
    bool primeiraLinha = true;
    int contador = 0;

    while (getline(arquivo, linha)) {
        if (linha[0] == '%') continue; // Ignorar comentários

        if (primeiraLinha) {
            stringstream ss(linha);
            ss >> numVertices >> numVertices >> numArestas;
            cout << "🔹 Número de Vértices: " << numVertices << ", Arestas: " << numArestas << endl;

            // Criamos a lista de adjacência
            listaAdj = new ListaAdj(numVertices);
            primeiraLinha = false;
            continue;
        }

        // Leitura das arestas
        int origem, destino, peso;
        stringstream ss(linha);
        ss >> origem >> destino >> peso;

        // Inserir aresta na lista de adjacência
        listaAdj->inserirAresta(origem - 1, destino - 1, peso);

        if (++contador % 100000 == 0) {
            cout << "🔄 Processando aresta " << contador << "..." << endl;
        }
    }

    arquivo.close();
    cout << "✅ Carregamento de " << numArestas << " arestas concluído!" << endl;
}
