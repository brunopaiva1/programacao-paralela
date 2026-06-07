// Defina um grafo acíclico direcionado relacionado a área do seu
// mestrado/doutorado e use a sua implementação para ordenar
// topologicamente esse grafo

#include <iostream>
#include <vector>
#include <queue>
#include <string>

class ArtigoDAG {
private:
    int V;
    std::vector<std::vector<int>> adj;
    std::vector<std::string> nomes;

public:
    ArtigoDAG(int vertices) : V(vertices), adj(vertices), nomes(vertices) {}

    void setNome(int v, std::string nome) {
        nomes[v] = nome;
    }

    void addAresta(int u, int v) {
        adj[u].push_back(v);
    }

    void ordenacaoTopologica() {
        std::vector<int> grauEntrada(V, 0);
        for (int u = 0; u < V; u++) {
            for (int v : adj[u]) {
                grauEntrada[v]++;
            }
        }

        std::priority_queue<int, std::vector<int>, std::greater<int>> q;
        for (int i = 0; i < V; i++) {
            if (grauEntrada[i] == 0) {
                q.push(i);
            }
        }

        std::vector<int> ordem;
        int count = 0;

        while (!q.empty()) {
            int u = q.top();
            q.pop();
            ordem.push_back(u);
            count++;

            for (int v : adj[u]) {
                grauEntrada[v]--;
                if (grauEntrada[v] == 0) {
                    q.push(v);
                }
            }
        }

        if (count != V) {
            std::cout << "Erro: Ciclo detectado no grafo.\n";
            return;
        }

        std::cout << "Ordenacao Topologica do Artigo Academico:\n";
        for (size_t i = 0; i < ordem.size(); i++) {
            std::cout << i + 1 << ". " << nomes[ordem[i]] << "\n";
        }
    }
};

int main() {
    ArtigoDAG dag(8);

    dag.setNome(0, "Revisao Bibliografica");
    dag.setNome(1, "Execucao dos Experimentos");
    dag.setNome(2, "Analise dos Resultados");
    dag.setNome(3, "Escrita da Metodologia");
    dag.setNome(4, "Escrita da Introducao");
    dag.setNome(5, "Escrita dos Resultados e Discussao");
    dag.setNome(6, "Revisao");
    dag.setNome(7, "Submissão final");

    dag.addAresta(0, 1); 
    dag.addAresta(1, 2); 
    dag.addAresta(2, 3); 
    dag.addAresta(3, 4); 
    dag.addAresta(4, 5); 
    dag.addAresta(5, 6); 
    dag.addAresta(4, 6); 
    dag.addAresta(3, 6);
    dag.addAresta(6, 7); 

    dag.ordenacaoTopologica();

    return 0;
}