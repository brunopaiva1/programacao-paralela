// 22. Mostre experimentalmente que a taxa de competitividade do algoritmo de mover 
// para a frente se aproxima de 4 estatisticamente.

#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include <iomanip>

using namespace std;

long long custo_otimo(const vector<int>& S, int n_size) {
    vector<pair<int, int>> frequencias(n_size);
    for (int i = 0; i < n_size; i++) frequencias[i] = {i + 1, 0};
    for (int key : S) frequencias[key - 1].second++;

    sort(frequencias.begin(), frequencias.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    });

    vector<int> lista_otima(n_size);
    for (int i = 0; i < n_size; i++) lista_otima[i] = frequencias[i].first;

    long long custo = 0;
    for (int key : S) {
        auto it = find(lista_otima.begin(), lista_otima.end(), key);
        int indice_0_based = distance(lista_otima.begin(), it);
        custo += (indice_0_based + 1); 
    }
    return custo;
}

long long custo_mtf(const vector<int>& S, vector<int> lista) {
    long long custo = 0;
    for (int key : S) {
        auto it = find(lista.begin(), lista.end(), key);
        int i = distance(lista.begin(), it); 
        
        custo += (2 * i) + 1;

        lista.erase(it);
        lista.insert(lista.begin(), key);
    }
    return custo;
}

int main() {
    random_device rd;
    mt19937 gen(42); 
    
    int n_size_aleatorio = 5;
    vector<int> base_aleatoria(n_size_aleatorio);
    iota(base_aleatoria.begin(), base_aleatoria.end(), 1);
    uniform_int_distribution<> dist(1, n_size_aleatorio);

    vector<int> acessos_N = {1000, 5000, 10000, 50000};
    
    for (int N : acessos_N) {
        vector<int> S(N);
        for(int i = 0; i < N; i++) S[i] = dist(gen);
        
        long long c_opt = custo_otimo(S, n_size_aleatorio);
        long long c_mtf = custo_mtf(S, base_aleatoria);
        
        cout << "N = " << setw(5) << N 
             << " | MTF = " << setw(7) << c_mtf 
             << " | OPT = " << setw(7) << c_opt 
             << " | Taxa = " << fixed << setprecision(5) << (double)c_mtf / c_opt << "\n";
    }
    cout << "\n";

    for (int N : acessos_N) {
        vector<int> S;
        while(S.size() < N) {
            for(int v : base_aleatoria) {
                if(S.size() < N) S.push_back(v);
            }
        }
        
        long long c_opt = custo_otimo(S, n_size_aleatorio);
        long long c_mtf = custo_mtf(S, base_aleatoria);
        
        cout << "N = " << setw(5) << N 
             << " | MTF = " << setw(7) << c_mtf 
             << " | OPT = " << setw(7) << c_opt 
             << " | Taxa = " << fixed << setprecision(5) << (double)c_mtf / c_opt << "\n";
    }
    cout << "\n";

    vector<int> tamanhos_n = {10, 50, 100, 500, 1000, 2000, 5000};
    int ciclos = 100; 
    
    for (int n_size : tamanhos_n) {
        vector<int> base(n_size);
        iota(base.begin(), base.end(), 1);
        
        vector<int> S;
        S.reserve(n_size * ciclos);
        for(int c = 0; c < ciclos; c++) {
            S.insert(S.end(), base.begin(), base.end());
        }
        
        long long c_opt = custo_otimo(S, n_size);
        long long c_mtf = custo_mtf(S, base);
        
        cout << "n_size = " << setw(4) << n_size 
             << " | MTF = " << setw(9) << c_mtf 
             << " | OPT = " << setw(9) << c_opt 
             << " | Taxa = " << fixed << setprecision(5) << (double)c_mtf / c_opt << "\n";
    }

    return 0;
}