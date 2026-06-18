/* File:     omp_trap_pag222_bloco2.c
 * Purpose:  Estimate definite integral using trapezoidal rule.
 * Uses manual private variable and critical section 
 * (NO reduction clause).
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
   long long int n;
   int     thread_count;
   double  start_time, end_time;

   if (argc != 2) Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);
   printf("Enter a, b, and n\n");
   scanf("%lf %lf %lld", &a, &b, &n);
   if (n % thread_count != 0) Usage(argv[0]);

   start_time = omp_get_wtime();

   /* --- AQUI ESTÁ A MÁGICA DA PÁGINA 222 (SEGUNDO BLOCO) --- */
#  pragma omp parallel num_threads(thread_count) 
   {
       /* 1. Cada thread cria sua própria variável local (privada) */
       double my_result = 0.0; 
       
       /* 2. As threads rodam a função pesada ao mesmo tempo, sem se bloquear */
       my_result = Local_trap(a, b, n);

       /* 3. Só na hora de somar no bolo principal é que elas usam a catraca (critical) */
#      pragma omp critical
       global_result += my_result;
   }
   /* -------------------------------------------------------- */

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
}

double f(double x) {
   return x*x;
}

double Local_trap(double a, double b, long long int n) {
   double  h, x, my_result;
   double  local_a, local_b;
   long long int i, local_n;
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
}