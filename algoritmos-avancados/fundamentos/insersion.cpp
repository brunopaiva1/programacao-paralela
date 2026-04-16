// 2. Implemente o algoritmo de ordenação por inserção e crie uma cópia anotada dele que mede o número de 
// operações no modelo da Random Access Machine  (RAM, seção 2.2 do livro do Cormen). 
// Usando entradas de tamanho crescente, mostre, em um gráfico, 
// quando o tempo de execução no modelo RAM diverge de medições em uma máquina real.

#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include <algorithm>

typedef int KeyType;

class RAMTracker {
public:
    unsigned long long total_ops = 0;
    void add(int n) { total_ops += n; }
};

void insertion_sort(std::vector<KeyType>& a) {
    int n = a.size();
    for (int i = 1; i < n; i++) {
        KeyType key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

unsigned long long insertion_sort_instrumented(std::vector<KeyType>& a) {
    RAMTracker tracker;
    int n = a.size();

    tracker.add(1); 
    for (int i = 1; i < n; i++) {
        tracker.add(2); 

        KeyType key = a[i];
        int j = i - 1;
        tracker.add(3); 

        while (j >= 0 && a[j] > key) {
            tracker.add(4); 
            a[j + 1] = a[j];
            tracker.add(4); 
            j--;
            tracker.add(2); 
        }
        tracker.add(1); 

        a[j + 1] = key;
        tracker.add(3); 
    }
    tracker.add(1); 

    return tracker.total_ops;
}

int main() {
    std::cout << "n,ram_ops,real_ns" << std::endl;

    for (int n = 16; n <= 524288; n *= 2) {
        std::vector<KeyType> base_vec(n);
        std::iota(base_vec.begin(), base_vec.end(), 1);
        std::reverse(base_vec.begin(), base_vec.end());

        std::vector<KeyType> v_ram = base_vec;
        std::vector<KeyType> v_real = base_vec;

        unsigned long long ram_ops = insertion_sort_instrumented(v_ram);

        auto t1 = std::chrono::high_resolution_clock::now();
        insertion_sort(v_real);
        auto t2 = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();

        std::cout << n << "," << ram_ops << "," << duration << std::endl;
    }

    return 0;
}