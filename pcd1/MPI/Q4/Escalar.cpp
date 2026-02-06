/* 4. Escreva um programa MPI que receba do usuário dois vetores e um escalar, todos lidos
pelo processo 0 e distribuídos entre os processos. O primeiro vetor deve ser multiplicado
pelo escalar. Para o segundo vetor, deve-se calcular a sua norma. Os resultados calcu-
lados devem ser coletados no processo 0, que os imprime. Você pode assumir que n, a
ordem dos vetores, é divisível por comm_sz */

#include <iostream>
#include <vector>
#include <cmath>
#include <mpi.h>

int main(int argc, char** argv) {
    int comm_sz, my_rank;
    int n;
    double scalar;
    std::vector<double> vector1, vector2;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0) {
        std::cout << "Enter the size of the vectors (n): ";
        std::cin >> n;

        vector1.resize(n);
        vector2.resize(n);

        std::cout << "Enter the elements of the first vector:\n";
        for (int i = 0; i < n; ++i) {
            std::cin >> vector1[i];
        }

        std::cout << "Enter the elements of the second vector:\n";
        for (int i = 0; i < n; ++i) {
            std::cin >> vector2[i];
        }

        std::cout << "Enter the scalar value: ";
        std::cin >> scalar;
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&scalar, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    int local_n = n / comm_sz;
    std::vector<double> local_vector1(local_n);
    std::vector<double> local_vector2(local_n);

    MPI_Scatter(vector1.data(), local_n, MPI_DOUBLE, local_vector1.data(), local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(vector2.data(), local_n, MPI_DOUBLE, local_vector2.data(), local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double local_norm = 0.0;
    for (int i = 0; i < local_n; ++i) {
        local_vector1[i] *= scalar;
        local_norm += local_vector2[i] * local_vector2[i];
    }

    MPI_gather(local_vector1.data(), local_n, MPI_DOUBLE, vector1.data(), local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    double global_norm = 0.0;
    MPI_Reduce(&local_norm, &global_norm, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if(my_rank == 0) {
        global_norm = std::sqrt(global_norm);
        std::cout << "Result of the first vector after multiplication by scalar:\n";
        for (const auto& val : vector1) {
            std::cout << val << " ";
        }
        std::cout << "\nNorm of the second vector: " << global_norm << std::endl;
    }
    MPI_Finalize();
    return 0;
}