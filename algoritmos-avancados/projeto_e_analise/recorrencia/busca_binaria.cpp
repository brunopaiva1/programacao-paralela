#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <numeric>
#include <random>

using namespace std;
using KeyType = int;

KeyType binary_search_recursive(const vector<KeyType>& v, KeyType key, int begin, int end) {
    if (begin > end) return -1;
    
    int middle = begin + (end - begin) / 2; 
    if (key < v[middle]) {
        return binary_search_recursive(v, key, begin, middle - 1);
    } else if (key > v[middle]) {
        return binary_search_recursive(v, key, middle + 1, end);
    } else {
        return middle;
    }
}

int main() {
    ofstream csv("benchmark_busca.csv");
    csv << "n,tempo_ns\n";

    unsigned int max_n = 1 << 28; 
    int repeticoes = 50000;      
    mt19937 gen(42); 
    cout << "Iniciando benchmark da Busca Binária..." << endl;

    for (unsigned int n = 16; n <= max_n; n *= 2) {
        vector<KeyType> v(n);
        iota(v.begin(), v.end(), 1); 
        
        uniform_int_distribution<KeyType> distrib(1, n);
        
        vector<KeyType> chaves(repeticoes);
        for(int i = 0; i < repeticoes; i++) {
            chaves[i] = distrib(gen);
        }

        volatile KeyType sink = 0;
        
        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < repeticoes; i++) {
            sink = binary_search_recursive(v, chaves[i], 0, n - 1);
        }
        auto end = chrono::high_resolution_clock::now();
        
        chrono::duration<double, std::nano> elapsed = end - start;
        double tempo_medio_ns = elapsed.count() / repeticoes;

        csv << n << "," << tempo_medio_ns << "\n";
        cout << "N = 2^" << __builtin_ctz(n) << " | Tempo: " << tempo_medio_ns << " ns\n";
    }

    csv.close();
    cout << "Dados salvos em benchmark_busca.csv" << endl;
    return 0;
}