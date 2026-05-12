#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

int min_value(const std::vector<int> &a) {
    int res = a[0];
    for (size_t i = 1; i < a.size(); i++) {
        if (a[i] < res) res = a[i];
    }
    return res;
}

int max_value(const std::vector<int> &a) {
    int res = a[0];
    for (size_t i = 1; i < a.size(); i++) {
        if (a[i] > res) res = a[i];
    }
    return res;
}

void min_max(const std::vector<int> &a, int &min, int &max) {
    int n = a.size();
    int start;

    if (n % 2 == 0) {
        if (a[0] < a[1]) {
            min = a[0];
            max = a[1];
        } else {
            min = a[1];
            max = a[0];
        }
        start = 2;
    } else {
        min = a[0];
        max = a[0];
        start = 1;
    }

    for (int i = start; i < n; i += 2) {
        int local_min, local_max;

        if (a[i] < a[i + 1]) {
            local_min = a[i];
            local_max = a[i + 1];
        } else {
            local_min = a[i + 1];
            local_max = a[i];
        }

        if (local_min < min) min = local_min;
        if (local_max > max) max = local_max;
    }
}

double get_median(std::vector<double>& times) {
    std::sort(times.begin(), times.end());
    return times[times.size() / 2];
}

int main() {
    int n = 500000000;
    std::vector<int> a(n);

    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(0, 1000000000);
    for (int i = 0; i < n; i++) {
        a[i] = dist(gen);
    }

    const int NUM_RUNS = 5;
    std::vector<double> times_non_simul;
    std::vector<double> times_simul;

    int m1, M1, val_min, val_max;

    for (int r = 0; r < NUM_RUNS; r++) {
        std::cout << "Execução " << r + 1 << "\n";

        auto start_1 = std::chrono::high_resolution_clock::now();
        m1 = min_value(a);
        M1 = max_value(a);
        auto stop_1 = std::chrono::high_resolution_clock::now();
        
        times_non_simul.push_back(std::chrono::duration<double>(stop_1 - start_1).count());

        auto start_2 = std::chrono::high_resolution_clock::now();
        min_max(a, val_min, val_max);
        auto stop_2 = std::chrono::high_resolution_clock::now();
        
        times_simul.push_back(std::chrono::duration<double>(stop_2 - start_2).count());
    }

    std::cout << "Nao-simultaneo: " << get_median(times_non_simul) << " segundos\n";
    std::cout << "Simultaneo:     " << get_median(times_simul) << " segundos\n";

    std::cout << "\n(Controle - Max: " << M1 << " | Min: " << m1 << ")\n";

    return 0;
}