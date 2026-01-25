/* 5. Considere o seguinte laço:
a[0] = 0;
for ( i = 1; i < n ; i++)
a[i] = a[i-1] + i;
Há claramente uma dependência no laço já que o valor de a[i] não pode ser calculado
sem o valor de a[i-1]. Sugira uma maneira de eliminar essa dependência e paralelizar
o laço. */

#include <iostream>
#include <omp.h>
#include <vector>

int main(){
    long long n;

    std::cout << "Enter the value of n: ";
    std::cin >> n;

    std::vector<long long> a(n);
    std::vector<long long> a_parallel(n);

    // trecho de código serial com dependência de dados

    double start_serial = omp_get_wtime();
    a[0] = 0;
    for (long long i = 1; i < n; i++) {
        a[i] = a[i-1] + i;
    }

    double end_serial = omp_get_wtime();
    std::cout << "Serial execution time: " << (end_serial - start_serial) << " seconds" << std::endl;

    // trecho de código paralelo sem dependência de dados

    omp_set_num_threads(8);

    double start_parallel = omp_get_wtime();
    a_parallel[0] = 0;

    #pragma omp parallel for
    for (long long i = 1; i < n; i++) {
        a_parallel[i] = (i * (i + 1)) / 2; // Progressão aritmética de Gauss
    }

    double end_parallel = omp_get_wtime();
    std::cout << "Parallel execution time: " << (end_parallel - start_parallel) << " seconds" << std::endl;

    return 0;

}