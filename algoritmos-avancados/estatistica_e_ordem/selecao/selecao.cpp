#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <chrono>

int particiona(std::vector<int> &A, int p, int r) {
    int x = A[r];
    int i = p - 1;
    for (int j = p; j < r; ++j) {
        if (A[j] <= x) {
            ++i;
            std::swap(A[i], A[j]);
        }
    }
    std::swap(A[i + 1], A[r]);
    return i + 1;
}

int particiona_valor(std::vector<int> &A, int p, int r, int pivot_val) {
    int i;
    for (i = p; i < r; i++) {
        if (A[i] == pivot_val) break;
    }
    std::swap(A[i], A[r]); 
    return particiona(A, p, r);
}

int particiona_aleatorizado(std::vector<int> &A, int p, int r) {
    int i = p + rand() % (r - p + 1);
    std::swap(A[i], A[r]);
    return particiona(A, p, r);
}

int randomized_select(std::vector<int> &A, int p, int r, int i) {
    if (p == r) return A[p];
    
    int q = particiona_aleatorizado(A, p, r);
    int k = q - p + 1;
    
    if (i == k) return A[q];
    else if (i < k) return randomized_select(A, p, q - 1, i);
    else return randomized_select(A, q + 1, r, i - k);
}

int encontra_mediana(std::vector<int> &A, int inicio, int n) {
    std::sort(A.begin() + inicio, A.begin() + inicio + n);
    return A[inicio + n / 2];
}

int deterministic_select(std::vector<int> &A, int p, int r, int i) {
    int n = r - p + 1;
    if (n <= 5) {
        std::sort(A.begin() + p, A.begin() + r + 1);
        return A[p + i - 1];
    }
    
    std::vector<int> medianas;
    for (int j = 0; j < n / 5; j++) {
        medianas.push_back(encontra_mediana(A, p + j * 5, 5));
    }
    if (n % 5 != 0) {
        medianas.push_back(encontra_mediana(A, p + (n / 5) * 5, n % 5));
    }
    
    int val_mediana_das_medianas = deterministic_select(medianas, 0, medianas.size() - 1, medianas.size() / 2 + 1);
    
    int q = particiona_valor(A, p, r, val_mediana_das_medianas);
    int k = q - p + 1;
    
    if (i == k) return A[q];
    else if (i < k) return deterministic_select(A, p, q - 1, i);
    else return deterministic_select(A, q + 1, r, i - k);
}

int main() {
    srand(42);
    int n = 1000000;
    int iesimo = 1;

    std::vector<int> v(n);
    std::iota(v.begin(), v.end(), 1);
    // std::shuffle(v.begin(), v.end(), std::mt19937(42));

    std::vector<int> v_det = v;
    std::vector<int> v_rand = v;

    auto start1 = std::chrono::high_resolution_clock::now();
    int res1 = deterministic_select(v_det, 0, n - 1, iesimo);
    auto end1 = std::chrono::high_resolution_clock::now();
    double tempo_det = std::chrono::duration<double>(end1 - start1).count();

    auto start2 = std::chrono::high_resolution_clock::now();
    int res2 = randomized_select(v_rand, 0, n - 1, iesimo);
    auto end2 = std::chrono::high_resolution_clock::now();
    double tempo_rand = std::chrono::duration<double>(end2 - start2).count();

    std::cout << "Secao 9.3 (Deterministico): " << tempo_det << " s\n";
    std::cout << "Secao 9.2 (Aleatorio):      " << tempo_rand << " s\n";
    std::cout << res1 << " " << res2 << "\n";

    return 0;
}