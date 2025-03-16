#include "AlgoritmoRandomizado.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

 //Construtor: inicializa o objeto e define o menor custo como infinito (INT_MAX)
AlgoritmoRandomizado::AlgoritmoRandomizado(const GrafoMatriz& g) : grafo(g), menorCusto(INT_MAX), 
                    numCidades(g.getNumVertices()), melhorRota(nullptr) {}


// Método que resolve o problema do caixeiro viajante usando um algoritmo randomizado
void AlgoritmoRandomizado::resolver(double iteracoes) {
    //int numCidades = obterNumCidades();
    int numCidades = grafo.getNumVertices();
    int* cidades = new int[numCidades];

    // Preenche o array com todas as cidades disponíveis
    for (int i = 0; i < numCidades; i++) {
        cidades[i] = i;
    }

    // Inicializa a semente do gerador de números aleatórios para garantir diversidade nos testes
    srand(time(nullptr));

    // Executa o algoritmo por um número determinado de iterações
    for (int i = 0; i < iteracoes; i++) {
        // Embaralha aleatoriamente a ordem das cidades para gerar uma nova solução
        for (int j = numCidades - 1; j > 0; j--) {
            int k = rand() % (j + 1);
            swap(cidades[j], cidades[k]);
        }

        // Calcula o custo da rota atual
        int custoAtual = 0;
        for (int j = 0; j < numCidades - 1; j++) {
            custoAtual += obterDistancia(cidades[j], cidades[j + 1]);
        }
        // Fecha o ciclo voltando para a cidade inicial
        custoAtual += obterDistancia(cidades[numCidades - 1], cidades[0]);

        // Se o custo encontrado for melhor, atualiza a melhor rota e o menor custo
        if (custoAtual < menorCusto) {
            menorCusto = custoAtual;
            // Copia a rota atual para a melhor rota
            delete[] melhorRota;
            melhorRota = new int[numCidades];
            for (int j = 0; j < numCidades; j++) {
                melhorRota[j] = cidades[j];
            }
        }
    }

    delete[] cidades;
}

// Método que exibe a melhor rota encontrada e seu custo
void AlgoritmoRandomizado::exibirMelhorRota() const {
    cout << "Melhor rota encontrada: ";
    for (int i = 0; i < obterNumCidades(); i++) {
        cout << melhorRota[i] << " -> ";
    }
    cout << melhorRota[0] << endl; // Fecha o ciclo voltando para a cidade inicial
    if (melhorRota == nullptr) {
    cout << "Nenhuma rota encontrada." << endl;
    return;
}

    cout << "Custo: " << menorCusto << endl;
}

// Destrutor para liberar a memória alocada dinamicamente
AlgoritmoRandomizado::~AlgoritmoRandomizado() {
    if (melhorRota != nullptr) {
    delete[] melhorRota;
}
melhorRota = new int[numCidades];

}

// Retorna a distância entre duas cidades
int AlgoritmoRandomizado::obterDistancia(int cidade1, int cidade2) const {
    int numCidades = grafo.getNumVertices();

    if (cidade1 >= 0 && cidade1 < numCidades && cidade2 >= 0 && cidade2 < numCidades) {
        return grafo.obterDistancia(cidade1,cidade2);
    } else {
        throw out_of_range("Cidade fora do intervalo válido.");
    }
}

// Retorna o número de cidades no grafo
int AlgoritmoRandomizado::obterNumCidades() const {
    return numCidades;
}


/*#include "AlgoritmoRandomizado.h"
#include <iostream>
#include <climits>

using namespace std;

// Construtor
AlgoritmoRandomizado::AlgoritmoRandomizado(const GrafoMatriz& g) 
    : grafo(g), menorCusto(INT_MAX), numCidades(g.getNumVertices()), melhorRota(nullptr) {}

// Destrutor
AlgoritmoRandomizado::~AlgoritmoRandomizado() {
    if (melhorRota != nullptr) {
        delete[] melhorRota;
    }
}

// Método para resolver o problema do caixeiro viajante usando o algoritmo do vizinho mais próximo
void AlgoritmoRandomizado::resolver() {
    int* cidades = new int[numCidades];
    bool* visitado = new bool[numCidades]();

    // Escolhe a cidade inicial (pode ser qualquer uma, aqui escolhemos a cidade 0)
    int cidadeAtual = 0;
    cidades[0] = cidadeAtual;
    visitado[cidadeAtual] = true;

    // Constrói a rota usando o algoritmo do vizinho mais próximo
    for (int i = 1; i < numCidades; i++) {
        int cidadeMaisProxima = -1;
        int menorDistancia = INT_MAX;

        // Encontra a cidade mais próxima que ainda não foi visitada
        for (int j = 0; j < numCidades; j++) {
            if (!visitado[j]) {
                int distancia = obterDistancia(cidadeAtual, j);
                if (distancia < menorDistancia) {
                    menorDistancia = distancia;
                    cidadeMaisProxima = j;
                }
            }
        }

        // Adiciona a cidade mais próxima à rota
        cidades[i] = cidadeMaisProxima;
        visitado[cidadeMaisProxima] = true;
        cidadeAtual = cidadeMaisProxima;
    }

    // Calcula o custo da rota encontrada
    int custoAtual = 0;
    for (int i = 0; i < numCidades - 1; i++) {
        custoAtual += obterDistancia(cidades[i], cidades[i + 1]);
    }
    custoAtual += obterDistancia(cidades[numCidades - 1], cidades[0]);

    // Atualiza a melhor rota e o menor custo
    menorCusto = custoAtual;
    delete[] melhorRota;
    melhorRota = new int[numCidades];
    for (int i = 0; i < numCidades; i++) {
        melhorRota[i] = cidades[i];
    }

    delete[] cidades;
    delete[] visitado;
}

// Método para exibir a melhor rota encontrada
void AlgoritmoRandomizado::exibirMelhorRota() const {
    if (melhorRota == nullptr) {
        cout << "Nenhuma rota encontrada." << endl;
        return;
    }

    cout << "Melhor rota encontrada: ";
    for (int i = 0; i < numCidades; i++) {
        cout << melhorRota[i] << " -> ";
    }
    cout << melhorRota[0] << endl; // Fecha o ciclo voltando para a cidade inicial
    cout << "Custo: " << menorCusto << endl;
}

// Método para obter a distância entre duas cidades
int AlgoritmoRandomizado::obterDistancia(int cidade1, int cidade2) const {
    if (cidade1 >= 0 && cidade1 < numCidades && cidade2 >= 0 && cidade2 < numCidades) {
        return grafo.obterDistancia(cidade1, cidade2);
    } else {
        throw out_of_range("Cidade fora do intervalo válido.");
    }
}

// Método para obter o número de cidades
int AlgoritmoRandomizado::obterNumCidades() const {
    return numCidades;
}*/