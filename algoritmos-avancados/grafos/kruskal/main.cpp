// Implemente e aponte vantagens e desvantagens dos algoritmos de
// Kruskal e Prim para gerar uma árvore de abrangência mínima. Use
// exemplos práticos da sua área para demonstrar suas conclusões.

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <chrono>
#include <random>
#include <iomanip>

struct Aresta {
    int u, v;
    double peso;
    bool operator<(const Aresta& outra) const {
        return peso < outra.peso;
    }
};

class DSU {
    std::vector<int> pai, rank;
public:
    DSU(int n) {
        pai.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) pai[i] = i;
    }
    int encontrar(int i) {
        if (pai[i] == i) return i;
        return pai[i] = encontrar(pai[i]);
    }
    void unir(int i, int j) {
        int raiz_i = encontrar(i);
        int raiz_j = encontrar(j);
        if (raiz_i != raiz_j) {
            if (rank[raiz_i] < rank[raiz_j]) pai[raiz_i] = raiz_j;
            else if (rank[raiz_i] > rank[raiz_j]) pai[raiz_j] = raiz_i;
            else {
                pai[raiz_j] = raiz_i;
                rank[raiz_i]++;
            }
        }
    }
};

class MSTBenchmark {
private:
    int V;
    std::vector<Aresta> arestas;
    std::vector<std::vector<std::pair<int, double>>> adj;

public:
    MSTBenchmark(int vertices) : V(vertices), adj(vertices) {}

    void addAresta(int u, int v, double peso) {
        arestas.push_back({u, v, peso});
        adj[u].push_back({v, peso});
        adj[v].push_back({u, peso});
    }

    void kruskal() {
        auto start = std::chrono::high_resolution_clock::now();
        
        double custo_mst = 0;
        int arestas_mst = 0;
        DSU dsu(V);

        std::vector<Aresta> arestas_ordenadas = arestas; 
        std::sort(arestas_ordenadas.begin(), arestas_ordenadas.end());

        for (const auto& aresta : arestas_ordenadas) {
            if (dsu.encontrar(aresta.u) != dsu.encontrar(aresta.v)) {
                dsu.unir(aresta.u, aresta.v);
                custo_mst += aresta.peso;
                arestas_mst++;
                if (arestas_mst == V - 1) break;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> tempo = end - start;

        std::cout << "[Kruskal]\n";
        std::cout << "  Custo Total: " << custo_mst << "\n";
        std::cout << "  Tempo: " << tempo.count() << " ms\n";
    }

    void prim() {
        auto start = std::chrono::high_resolution_clock::now();
        
        double custo_mst = 0;
        std::vector<bool> na_mst(V, false);
        int arestas_mst = 0;
        
        using pdi = std::pair<double, int>;
        std::priority_queue<pdi, std::vector<pdi>, std::greater<pdi>> pq;

        pq.push({0.0, 0});

        while (!pq.empty() && arestas_mst < V) {
            double peso = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (na_mst[u]) continue;
            
            na_mst[u] = true;
            custo_mst += peso;
            arestas_mst++;

            for (const auto& vizinho : adj[u]) {
                int v = vizinho.first;
                double peso_vizinho = vizinho.second;
                if (!na_mst[v]) {
                    pq.push({peso_vizinho, v});
                }
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> tempo = end - start;

        std::cout << "[Prim com Binary Heap]\n";
        std::cout << "  Custo Total: " << custo_mst << "\n";
        std::cout << "  Tempo: " << tempo.count() << " ms\n";
    }
};

void cenarioEsparso() {
    std::cout << "--- Questao 1: Grafo Esparso (Rede de Cluster Fisica) ---\n";
    std::cout << "Vertices (V): 10, Arestas (E): 17\n";
    
    MSTBenchmark cluster(10);
    
    for(int i = 0; i < 8; i++) cluster.addAresta(i, 8, 1.0);
    cluster.addAresta(8, 9, 2.0);
    for(int i = 0; i < 8; i++) cluster.addAresta(i, 9, 3.0);

    cluster.kruskal();
    cluster.prim();
}

void cenarioDenso() {
    int V = 500;
    int E = (V * (V - 1)) / 2;
    std::cout << "\n--- Questao 2: Grafo Denso (Simulacao de Matriz Logica) ---\n";
    std::cout << "Vertices (V): " << V << ", Arestas (E): " << E << "\n";
    
    MSTBenchmark grafo_denso(V);
    
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(0.5, 10.0);

    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            grafo_denso.addAresta(i, j, dist(rng));
        }
    }

    grafo_denso.kruskal();
    grafo_denso.prim();
}

int main() {
    std::cout << std::fixed << std::setprecision(4);
    cenarioEsparso();
    cenarioDenso();
    return 0;
}