#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;
using namespace std::chrono;

int partition_det(vector<int>& A, int p, int r) {
    int x = A[r];
    int i = p - 1;
    for (int j = p; j <= r - 1; j++) {
        if (A[j] <= x) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    return i + 1;
}

void quicksort_det(vector<int>& A, int p, int r) {
    if (p < r) {
        int q = partition_det(A, p, r);
        quicksort_det(A, p, q - 1);
        quicksort_det(A, q + 1, r);
    }
}

int partition_rand(vector<int>& A, int p, int r, mt19937& gen) {
    uniform_int_distribution<> dist(p, r);
    int i = dist(gen);
    swap(A[i], A[r]);
    return partition_det(A, p, r);
}

void quicksort_rand(vector<int>& A, int p, int r, mt19937& gen) {
    if (p < r) {
        int q = partition_rand(A, p, r, gen);
        quicksort_rand(A, p, q - 1, gen);
        quicksort_rand(A, q + 1, r, gen);
    }
}

vector<int> generate_vector(int n, const string& type, mt19937& gen) {
    vector<int> v(n);
    iota(v.begin(), v.end(), 1);
    if (type == "average") {
        shuffle(v.begin(), v.end(), gen);
    }
    return v;
}

double benchmark_det(vector<int> arr) {
    auto start = high_resolution_clock::now();
    quicksort_det(arr, 0, arr.size() - 1);
    auto end = high_resolution_clock::now();
    return duration<double, milli>(end - start).count();
}

double benchmark_rand(vector<int> arr, mt19937& gen) {
    auto start = high_resolution_clock::now();
    quicksort_rand(arr, 0, arr.size() - 1, gen);
    auto end = high_resolution_clock::now();
    return duration<double, milli>(end - start).count();
}

int main() {
    mt19937 gen(42);
    long long max_size = 65536;
    int num_repeats = 5;

    ofstream file("benchmark_quicksort.csv");
    file << "algorithm,case,n,time_ms\n";

    vector<string> cases = {"average", "worst"};

    cout << "Iniciando Benchmark do Quicksort...\n";

    for (int n = 16; n <= max_size; n *= 2) {
        cout << "Processando N = " << n << "\n";
        for (const auto& c : cases) {
            double avg_det = 0.0;
            double avg_rand = 0.0;

            for (int run = 0; run < num_repeats; run++) {
                auto original = generate_vector(n, c, gen);
                avg_det += benchmark_det(original);
                avg_rand += benchmark_rand(original, gen);
            }

            avg_det /= num_repeats;
            avg_rand /= num_repeats;

            file << "Padrão," << c << "," << n << "," << avg_det << "\n";
            file << "Aleatório," << c << "," << n << "," << avg_rand << "\n";
        }
    }
    file.close();
    cout << "Dados exportados para benchmark_quicksort.csv\n";
    return 0;
}