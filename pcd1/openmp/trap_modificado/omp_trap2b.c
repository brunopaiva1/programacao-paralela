/* File:     omp_trap2b.c
 * Purpose:  Estimate definite integral using trapezoidal rule with reduction.
 * Compile:  gcc -g -Wall -fopenmp -o omp_trap2b omp_trap2b.c
 * Usage:    ./omp_trap2b <number of threads>
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void Usage(char* prog_name);
double f(double x);
double Local_trap(double a, double b, long long int n);

int main(int argc, char* argv[]) {
   double  global_result = 0.0;
   double  a, b;
   long long int n;              /* Alterado para suportar bilhões */
   int     thread_count;
   double  start_time, end_time; /* Variáveis de tempo */

   if (argc != 2) Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);
   printf("Enter a, b, and n\n");
   scanf("%lf %lf %lld", &a, &b, &n); /* Lendo como long long int */
   if (n % thread_count != 0) Usage(argv[0]);

   /* Inicia a contagem do tempo */
   start_time = omp_get_wtime();

#  pragma omp parallel num_threads(thread_count) \
      reduction(+: global_result)
   global_result += Local_trap(a, b, n);

   /* Finaliza a contagem do tempo */
   end_time = omp_get_wtime();

   printf("With n = %lld trapezoids, our estimate\n", n);
   printf("of the integral from %f to %f = %.14e\n", a, b, global_result);
   printf("Tempo gasto no bloco paralelo: %f segundos\n", end_time - start_time);

   return 0;
}  /* main */

void Usage(char* prog_name) {
   fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
   fprintf(stderr, "   number of trapezoids must be evenly divisible by\n");
   fprintf(stderr, "   number of threads\n");
   exit(0);
}  /* Usage */

double f(double x) {
   return x*x;
}  /* f */

double Local_trap(double a, double b, long long int n) {
   double  h, x, my_result;
   double  local_a, local_b;
   long long int i, local_n; /* Alterado para suportar bilhões */
   int my_rank = omp_get_thread_num();
   int thread_count = omp_get_num_threads();

   h = (b-a)/n; 
   local_n = n/thread_count;  
   local_a = a + my_rank*local_n*h; 
   local_b = local_a + local_n*h; 
   my_result = (f(local_a) + f(local_b))/2.0; 
   
   for (i = 1; i <= local_n-1; i++) {
     x = local_a + i*h;
     my_result += f(x);
   }
   my_result = my_result*h; 

   return my_result;
}  /* Local_trap */