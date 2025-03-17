# 📌 Trabalho de Grafos - Caixeiro Viajante (TSP)

## 📖 Descrição do Problema

O **Problema do Caixeiro Viajante (TSP - Traveling Salesman Problem)** é um problema clássico da teoria dos grafos e otimização combinatória. O objetivo é encontrar o ciclo Hamiltoniano de menor custo em um grafo completo ponderado.

### 🔹 **Definição Formal**

- Dado um conjunto de **n cidades** e as **distâncias entre cada par de cidades**, encontrar um ciclo de **menor custo** que visite **todas as cidades exatamente uma vez** e retorne à cidade de origem.
- O problema é **NP-completo**, tornando inviável uma solução exata para grandes instâncias.

---

## 📁 Estrutura do Projeto

```
TrabalhoGrafos/
│── main.cpp                # Arquivo principal do projeto
│── README.md               # Documentação do projeto
│── docs/                   # Relatório e documentação técnica
│   ├── relatorio.pdf
│   ├── documentacao.pdf
│
│── include/                # Arquivos de cabeçalho (.h)
│   ├── grafo.h
│   ├── grafo_matriz.h
│   ├── grafo_lista.h
│   ├── tsp_loader.h
│   ├── mtx_loader.h
│   ├── ListaAdj.h
│
│── src/                    # Implementação dos métodos
│   ├── grafo.cpp
│   ├── grafo_matriz.cpp
│   ├── grafo_lista.cpp
│   ├── tsp_loader.cpp
│   ├── mtx_loader.cpp
│   ├── ListaAdj.cpp
│
│── entradas/               # Arquivos de entrada
│   ├── instancias/         # Instâncias do problema
│   │   ├── road-asia-osm.mtx
│   │   ├── road-germany-osm.mtx
│   │   ├── road-great-britain-osm.mtx
│   │   ├── road-italy-osm.edges
│   ├── grafo.txt
```

---

## ⚙️ Métodos Implementados

### 🔹 **1. Algoritmo Guloso**

- Começa em um vértice qualquer e escolhe sempre o **vizinho mais próximo**.
- **Complexidade:** `O(n²)`.
- **Desvantagem:** Pode levar a soluções ruins em alguns casos.

### 🔹 **2. Algoritmo Randomizado**

- Explora **K vizinhos aleatórios** ao invés de apenas o mais próximo.
- Introduz variabilidade para escapar de mínimos locais.
- **Complexidade:** `O(n log n)`, dependendo do número de iterações.

### 🔹 **3. Algoritmo Reativo**

- Variante aprimorada do algoritmo randomizado.
- Ajusta as probabilidades de escolha de cada estratégia conforme a execução avança.
- **Complexidade:** Depende da configuração dos pesos de adaptação.

---

## ⚙️ Compilação e Execução

### **Compilação**

Para compilar o código, execute:

```bash
g++ -o main.exe main.cpp src/*.cpp -I./include -g -Wall -Werror
```

### **Execução**

Para rodar o programa e processar uma instância:

```bash
./main.exe -p -m entradas/instancias/pla85900.mtx
```

### **Teste de Memória com Valgrind**

Para verificar vazamentos de memória:

```bash
valgrind ./main.exe -p -m entradas/instancias/pla85900.mtx
```

---

## 📥 Download das Instâncias

Os arquivos `.mtx` e `.edges` são grandes e não podem ser armazenados no GitHub.  
Baixe-os no seguinte link:  
🔗 **[Download das Instâncias TSP - Google Drive](https://drive.google.com/your-link-aqui)**

---

## 🏁 Conclusão

- A implementação suporta **grandes instâncias do TSP**, utilizando lista de adjacência para eficiência de memória.
- O **algoritmo reativo** apresentou os **melhores resultados**, ajustando a estratégia dinamicamente.
- A **lista de adjacência** foi **fundamental para evitar estouro de memória** em grafos grandes.
- O código está modularizado e permite **fácil expansão para novas heurísticas**.
