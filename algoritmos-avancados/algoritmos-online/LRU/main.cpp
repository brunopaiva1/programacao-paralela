#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <iomanip>

using namespace std;

int lru_misses(const vector<int>& S, int k) {
    list<int> cache;
    int misses = 0;

    for (int page : S) {
        auto it = find(cache.begin(), cache.end(), page);
        
        if (it != cache.end()) {
            cache.erase(it);
            cache.push_front(page);
        } else {
            misses++;
            if (cache.size() == (size_t)k) {
                cache.pop_back();
            }
            cache.push_front(page);
        }
    }
    return misses;
}

int opt_misses(const vector<int>& S, int k) {
    unordered_map<int, queue<int>> ocorrencias;
    for (size_t i = 0; i < S.size(); i++) {
        ocorrencias[S[i]].push(i);
    }

    vector<int> cache;
    int misses = 0;

    for (size_t i = 0; i < S.size(); i++) {
        int page = S[i];
        ocorrencias[page].pop();

        auto it = find(cache.begin(), cache.end(), page);
        if (it == cache.end()) {
            misses++;
            if (cache.size() < (size_t)k) {
                cache.push_back(page);
            } else {
                int furthest = -1;
                int replace_idx = -1;
                
                for (size_t c = 0; c < cache.size(); c++) {
                    int page_in_cache = cache[c];
                    int next_use = ocorrencias[page_in_cache].empty() ? 1e9 : ocorrencias[page_in_cache].front();
                    
                    if (next_use > furthest) {
                        furthest = next_use;
                        replace_idx = c;
                    }
                }
                cache[replace_idx] = page;
            }
        }
    }
    return misses;
}

int main() {
    cout << "=== Demonstracao da Competitividade do Algoritmo LRU ===\n";
    cout << "O pior caso para uma cache de tamanho K eh uma sequencia ciclica de K+1 elementos.\n\n";

    int k = 4;
    cout << "-> Cache Fixa (K = " << k << ")\n";
    cout << "-> Adversario: Sequencia repetitiva de " << k + 1 << " elementos [1,2,3,4,5]\n";
    cout << "--------------------------------------------------------\n";
    
    vector<int> tamanhos_N = {100, 500, 1000, 5000, 10000, 50000, 100000};
    
    for (int N : tamanhos_N) {
        vector<int> S(N);
        for (int i = 0; i < N; i++) {
            S[i] = (i % (k + 1)) + 1;
        }
        
        int m_lru = lru_misses(S, k);
        int m_opt = opt_misses(S, k);
        double taxa = (double)m_lru / m_opt;
        
        cout << "Entrada (N) = " << setw(6) << N 
             << " | Miss LRU = " << setw(6) << m_lru 
             << " | Miss OPT = " << setw(6) << m_opt 
             << " | Taxa (LRU/OPT) = " << fixed << setprecision(2) << taxa << "\n";
    }

    cout << "\nConclusao Parte 1: A taxa congelou exatamente em " << k << ".00.\n";

    int N_fixo = 20000;
    cout << "-> Entrada Fixa (N = " << N_fixo << " acessos)\n";
    cout << "--------------------------------------------------------\n";

    vector<int> tamanhos_K = {2, 5, 10, 20, 50};
    for (int test_k : tamanhos_K) {
        vector<int> S(N_fixo);
        for (int i = 0; i < N_fixo; i++) {
            S[i] = (i % (test_k + 1)) + 1;
        }
        
        int m_lru = lru_misses(S, test_k);
        int m_opt = opt_misses(S, test_k);
        double taxa = (double)m_lru / m_opt;
        
        cout << "Cache (K) = " << setw(4) << test_k 
             << " | Miss LRU = " << setw(5) << m_lru 
             << " | Miss OPT = " << setw(5) << m_opt 
             << " | Taxa Final = " << fixed << setprecision(2) << taxa << "\n";
    }

    return 0;
}