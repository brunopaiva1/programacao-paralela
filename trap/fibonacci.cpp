#include <iostream>
#include <omp.h>
#include <cstdlib>

long total_tarefas = 0;

int fib(int n) {
    #pragma omp critical
    total_tarefas++;

    if (n <= 1) return n;

    int x, y;

    #pragma omp task shared(x)
    x = fib(n - 1);

    #pragma omp task shared(y)
    y = fib(n - 2);

    #pragma omp taskwait

    return x + y;
}

int main(int argc, char* argv[]) {
    int n = 30;
    int resultado = 0;
    
    int threads = (argc > 1) ? std::atoi(argv[1]) : 4;
    omp_set_num_threads(threads);

    double inicio = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        {
            resultado = fib(n);
        }
    }

    double fim = omp_get_wtime();

    std::cout << "Fibonacci(" << n << ") = " << resultado << "\n";
    std::cout << "Total de tarefas geradas: " << total_tarefas << "\n";
    std::cout << "Tempo (" << threads << " threads): " << (fim - inicio) << " segundos\n";

    return 0;
}