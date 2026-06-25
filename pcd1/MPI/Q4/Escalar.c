#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int comm_sz, my_rank;
    int n;
    double scalar;
    double *vector1 = NULL;
    double *vector2 = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0) {
        printf("Enter the size of the vectors (n): ");
        scanf("%d", &n);

        vector1 = (double*)malloc(n * sizeof(double));
        vector2 = (double*)malloc(n * sizeof(double));

        printf("Enter the elements of the first vector:\n");
        for (int i = 0; i < n; ++i) {
            scanf("%lf", &vector1[i]);
        }

        printf("Enter the elements of the second vector:\n");
        for (int i = 0; i < n; ++i) {
            scanf("%lf", &vector2[i]);
        }

        printf("Enter the scalar value: ");
        scanf("%lf", &scalar);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&scalar, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    int local_n = n / comm_sz;
    
    double *local_vector1 = (double*)malloc(local_n * sizeof(double));
    double *local_vector2 = (double*)malloc(local_n * sizeof(double));

    MPI_Scatter(vector1, local_n, MPI_DOUBLE, local_vector1, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(vector2, local_n, MPI_DOUBLE, local_vector2, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double local_norm = 0.0;
    for (int i = 0; i < local_n; ++i) {
        local_vector1[i] *= scalar;
        local_norm += local_vector2[i] * local_vector2[i];
    }

    MPI_Gather(local_vector1, local_n, MPI_DOUBLE, vector1, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    double global_norm = 0.0;
    MPI_Reduce(&local_norm, &global_norm, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (my_rank == 0) {
        global_norm = sqrt(global_norm);
        printf("Result of the first vector after multiplication by scalar:\n");
        for (int i = 0; i < n; ++i) {
            printf("%g ", vector1[i]);
        }
        printf("\nNorm of the second vector: %g\n", global_norm);
    }

    free(local_vector1);
    free(local_vector2);
    
    if (my_rank == 0) {
        free(vector1);
        free(vector2);
    }

    MPI_Finalize();
    return 0;
}