#!/bin/bash
#SBATCH --job-name=optuna_lhs           
#SBATCH --output=results/saida_terminal_%j.txt    
#SBATCH --time=02:00:00              
#SBATCH --partition=intel-512         
#SBATCH --exclusive                     
#SBATCH --nodes=1                      
#SBATCH --ntasks-per-node=1             
#SBATCH --cpus-per-task=32
#SBATCH --mem=128000

module purge
module load compilers/gnu/14.2.0
module load libraries/openmpi/4.1.8-gnu8

TARGET="mergesort_omp"
SRC="main.cpp"
RESULT_FILE="results/benchmark_mediana.txt"

mkdir -p results

rm -f $TARGET
g++ -Wall -Wextra -O3 -fopenmp -std=c++17 -o $TARGET $SRC

if [ $? -eq 0 ]; then
    echo -e "Tamanho(N)\tThreads\tExecucao\tTempo(s)" > $RESULT_FILE
    
    for n in 1000000 5000000 10000000; do
        for t in 1 2 4 8 16 32; do
            for run in {1..5}; do
                SAIDA=$(./$TARGET $n $t)
                
                TEMPO=$(echo $SAIDA | cut -d',' -f3)
                
                echo -e "$n\t$t\t$run\t$TEMPO" >> $RESULT_FILE
            done
        done
    done
fi