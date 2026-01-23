/*4. Escreva um programa OpenMP que determine o escalonamento padrão de laços for
paralelos. Sua entrada deve ser o número de iterações e quantidade de threads e sua
saída deve ser quais iterações de um laço for paralelizado são executadas por qual
thread. Por exemplo, se houver duas threads e quatro iterações, a saída poderá ser:
Thread 0: Iterações 0 -- 1
Thread 1: Iterações 2 -- 3
(a) De acordo com a execução do seu programa, qual é o escalonamento padrão de
laços for paralelos de um programa OpenMP? Porque? */

#include <iostream>
#include <omp.h>
#include <vector>

int main() {
    int num_iterations;
    int num_threads;

    std::cout << "Enter number of iterations: ";
    std::cin >> num_iterations;
    std::cout << "Enter number of threads: ";
    std::cin >> num_threads;

    std::vector<int> iterations(num_iterations);

    omp_set_num_threads(num_threads);

    #pragma omp parallel for
    for (int i = 0; i < num_iterations; ++i) {
        iterations[i] = i;

        #pragma omp critical
        {
            std::cout << "Thread " << omp_get_thread_num() 
                      << ": Iteration " << iterations[i] << std::endl;
        }
    }

    return 0;
}