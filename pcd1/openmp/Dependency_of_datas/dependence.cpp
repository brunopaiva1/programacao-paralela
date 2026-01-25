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

    return 0;

}