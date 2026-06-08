#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <limits>
#include <algorithm>

const int INF = std::numeric_limits<int>::max();

struct Aresta {
    int destino;
    int tempo_minutos;
};

class MapaGPS {
private:
    int V;
    std::vector<std::vector<Aresta>> adj;
    std::vector<std::string> locais;

public:
    MapaGPS(int vertices) : V(vertices), adj(vertices), locais(vertices) {}

    void setNomeLocal(int id, std::string nome) {
        locais[id] = nome;
    }

    void addRua(int u, int v, int tempo) {
        adj[u].push_back({v, tempo});
        adj[v].push_back({u, tempo});
    }

    void dijkstra(int origem, int destino) {
        std::vector<int> dist(V, INF);
        std::vector<int> pai(V, -1);
        
        using pii = std::pair<int, int>;
        std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;

        dist[origem] = 0;
        pq.push({0, origem});

        while (!pq.empty()) {
            int tempo_atual = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (tempo_atual > dist[u]) continue;

            for (const auto& vizinho : adj[u]) {
                int v = vizinho.destino;
                int peso = vizinho.tempo_minutos;

                if (dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso; 
                    pai[v] = u;               
                    pq.push({dist[v], v});    
                }
            }
        }

        imprimirRota(origem, destino, dist, pai);
    }

private:
    void imprimirRota(int origem, int destino, const std::vector<int>& dist, const std::vector<int>& pai) {
        if (dist[destino] == INF) {
            std::cout << "Rota inacessivel!\n";
            return;
        }

        std::vector<int> caminho;
        for (int v = destino; v != -1; v = pai[v]) {
            caminho.push_back(v);
        }
        std::reverse(caminho.begin(), caminho.end());

        std::cout << "Menor latencia total: " << dist[destino] << " ms\n";
        std::cout << "Caminho a seguir:\n";
        for (size_t i = 0; i < caminho.size(); i++) {
            std::cout << locais[caminho[i]];
            if (i < caminho.size() - 1) std::cout << " -> ";
        }
        std::cout << "\n\n";

        std::cout << " Distancias de '" << locais[origem] << "' para todos os outros nos \n";
        for (int i = 0; i < V; i++) {
            std::cout << locais[origem] << " -> " << locais[i] << ": ";
            if (dist[i] == INF) {
                std::cout << "Inacessivel\n";
            } else {
                std::cout << dist[i] << " ms\n";
            }
        }
    }
};

int main() {
    MapaGPS mapa(6);

    mapa.setNomeLocal(0, "A");
    mapa.setNomeLocal(1, "B");
    mapa.setNomeLocal(2, "C");
    mapa.setNomeLocal(3, "D");
    mapa.setNomeLocal(4, "E");
    mapa.setNomeLocal(5, "F");

    mapa.addRua(0, 1, 5);
    mapa.addRua(0, 2, 2);
    mapa.addRua(1, 3, 4);
    mapa.addRua(1, 4, 2);
    mapa.addRua(2, 1, 8);
    mapa.addRua(2, 4, 7);
    mapa.addRua(3, 4, 6);
    mapa.addRua(3, 5, 3);
    mapa.addRua(4, 5, 1);

    mapa.dijkstra(0, 5);

    return 0;
}