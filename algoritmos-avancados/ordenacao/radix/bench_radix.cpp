#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <fstream>

using namespace std;
using namespace std::chrono;

void counting_sort(vector<int>& arr) {
    if(arr.empty()) return;
    int max_val = *max_element(arr.begin(), arr.end());
    vector<int> count(max_val + 1, 0);

    for(int x : arr) count[x]++;
    int idx = 0;
    for(int i = 0; i <= max_val; i++)
        while(count[i]--) arr[idx++] = i;
}

void counting_sort_digit(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    int count[10] = {0};

    for(int i = 0; i < n; i++) count[(arr[i]/exp) % 10]++;
    for(int i = 1; i < 10; i++) count[i] += count[i-1];

    for(int i = n-1; i >= 0; i--) {
        int digit = (arr[i]/exp) % 10;
        output[count[digit]-1] = arr[i];
        count[digit]--;
    }
    arr = output;
}

void radix_sort(vector<int>& arr) {
    if(arr.empty()) return;
    int max_val = *max_element(arr.begin(), arr.end());
    for(int exp = 1; max_val/exp > 0; exp *= 10)
        counting_sort_digit(arr, exp);
}

int main() {
    random_device rd;
    mt19937 rng(42); 
    uniform_int_distribution<int> dist_small(0, 1000);
    uniform_int_distribution<int> dist_large(0, 100000000);
    
    vector<int> sizes = {1000, 10000, 100000, 500000};
    int num_repeats = 3;

    ofstream file("benchmark_radix.csv");
    file << "algorithm,cenario,n,time_ms\n";

    cout << "=== Comparativo Radix vs Counting ===\n";

    for(auto n : sizes) {
        cout << "Processando N = " << n << "...\n";
        
        double avg_count_small = 0, avg_radix_small = 0;
        double avg_count_large = 0, avg_radix_large = 0;

        for(int r = 0; r < num_repeats; r++) {
            vector<int> v_small(n), v_large(n);
            for(int i = 0; i < n; i++) {
                v_small[i] = dist_small(rng);
                v_large[i] = dist_large(rng);
            }

            vector<int> temp = v_small;
            auto start = high_resolution_clock::now();
            counting_sort(temp);
            avg_count_small += duration<double, milli>(high_resolution_clock::now() - start).count();

            temp = v_small;
            start = high_resolution_clock::now();
            radix_sort(temp);
            avg_radix_small += duration<double, milli>(high_resolution_clock::now() - start).count();

            temp = v_large;
            start = high_resolution_clock::now();
            counting_sort(temp);
            avg_count_large += duration<double, milli>(high_resolution_clock::now() - start).count();

            temp = v_large;
            start = high_resolution_clock::now();
            radix_sort(temp);
            avg_radix_large += duration<double, milli>(high_resolution_clock::now() - start).count();
        }

        file << "Counting Sort,Pequenos," << n << "," << avg_count_small / num_repeats << "\n";
        file << "Radix Sort,Pequenos," << n << "," << avg_radix_small / num_repeats << "\n";
        file << "Counting Sort,Grandes," << n << "," << avg_count_large / num_repeats << "\n";
        file << "Radix Sort,Grandes," << n << "," << avg_radix_large / num_repeats << "\n";
    }

    file.close();
    cout << "Exportado para benchmark_radix.csv\n";
    return 0;
}
