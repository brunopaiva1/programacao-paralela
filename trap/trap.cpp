#include <iostream>
#include <iomanip>
#include <omp.h>
#include <cstdlib>

double f(double x) {
    return 4.0 / (1.0 + x * x);
}

int main(int argc, char* argv[]) {
    double a = 0.0, b = 1.0;
    
    long n = (argc > 2) ? std::atol(argv[2]) : 100000000;
    
    double h = (b - a) / n;

    int threads = (argc > 1) ? std::atoi(argv[1]) : 4;
    omp_set_num_threads(threads);

    double inicio = omp_get_wtime();

    double integral = (f(a) + f(b)) / 2.0;

    #pragma omp parallel for reduction(+:integral)
    for (long i = 1; i < n; i++) {
        double x = a + i * h;
        integral += f(x);
    }

    integral = integral * h; 

    double fim = omp_get_wtime();

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Valor de Pi calculado: " << integral << "\n";
    std::cout << "Tempo (" << threads << " threads, n=" << n << "): " << (fim - inicio) << " segundos\n";

    return 0;
}