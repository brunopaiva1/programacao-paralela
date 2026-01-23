// 11. Utilizando OpenMP, implemente o programa paralelo do histograma discutido no Capítulo
//2.

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define BIN_COUNT 6
#define DATA_COUNT 5000 

void find_bin(float value, float min_val, float max_val,
              int bin_count, int* bin_index) {

    if (value < min_val) {
        *bin_index = 0;
        return;
    }
    if (value >= max_val) {
        *bin_index = bin_count - 1;
        return;
    }

    float bin_width = (max_val - min_val) / bin_count;
    *bin_index = (int)((value - min_val) / bin_width);
}

int main() {
    float min_val = 0.0, max_val = 6.0;
    int bin_count = BIN_COUNT;
    int global_bin_counts[BIN_COUNT] = {0};
    double start_time, end_time;

    int data_size = DATA_COUNT / omp_get_max_threads();
    float* data = (float*)malloc(DATA_COUNT * sizeof(float));

    srand(time(NULL));
    for (int i = 0; i < DATA_COUNT; i++) {
        data[i] = (float)(rand() % 1000) / 100.0;
    }

    start_time = omp_get_wtime();
    #pragma omp parallel
{
    int local_bin_counts[BIN_COUNT] = {0};

    #pragma omp for
    for (int i = 0; i < DATA_COUNT; i++) {
        int bin_index;
        find_bin(data[i], min_val, max_val, bin_count, &bin_index);
        local_bin_counts[bin_index]++;
    }

    #pragma omp critical
    {
        for (int i = 0; i < BIN_COUNT; i++) {
            global_bin_counts[i] += local_bin_counts[i];
        }
    }
}

    end_time = omp_get_wtime();

    std::cout << "Tempo de execução: " << (end_time - start_time) << " segundos" << std::endl;
    std::cout << "Histograma:" << std::endl;
    for (int i = 0; i < BIN_COUNT; i++) {
    std::cout << "Bin " << i << ": " << global_bin_counts[i] <<  " valores" <<std::endl;
    }

    free(data);
    return 0;
}