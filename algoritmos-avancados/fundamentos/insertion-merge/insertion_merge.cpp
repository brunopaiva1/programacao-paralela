#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <random>

void insertion_sort(std::vector<int>& a) {
    for (int i = 1; i < a.size(); i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

void merge(std::vector<int>& a, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = a[p + i];
    for (int j = 0; j < n2; j++) R[j] = a[q + 1 + j];
    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) a[k++] = L[i++];
        else a[k++] = R[j++];
    }
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
}

void merge_sort(std::vector<int>& a, int p, int r) {
    if (p < r) {
        int q = p + (r - p) / 2;
        merge_sort(a, p, q);
        merge_sort(a, q + 1, r);
        merge(a, p, q, r);
    }
}

long long measure(std::vector<int> a, std::string algo) {
    auto t1 = std::chrono::high_resolution_clock::now();
    if (algo == "insertion") insertion_sort(a);
    else merge_sort(a, 0, a.size() - 1);
    auto t2 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
}

int main() {
    std::cout << "n,algo,cenario,tempo_ns" << std::endl;
    std::vector<int> tamanhos = {10, 50, 100, 500, 1000, 5000, 10000};
    std::mt19937 rng(42);

    for (int n : tamanhos) {
        std::vector<int> melhor(n), pior(n), medio(n);
        std::iota(melhor.begin(), melhor.end(), 1);
        pior = melhor;
        std::reverse(pior.begin(), pior.end());
        medio = melhor;
        std::shuffle(medio.begin(), medio.end(), rng);

        std::string algos[] = {"insertion", "merge"};
        for (auto& algo : algos) {
            std::cout << n << "," << algo << ",melhor," << measure(melhor, algo) << std::endl;
            std::cout << n << "," << algo << ",medio," << measure(medio, algo) << std::endl;
            std::cout << n << "," << algo << ",pior," << measure(pior, algo) << std::endl;
        }
    }
    return 0;
}