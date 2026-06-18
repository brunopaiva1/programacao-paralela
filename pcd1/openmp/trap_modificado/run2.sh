#!/bin/bash

# Define os nomes dos arquivos
SOURCE="omp_trap2b.c"
EXEC="omp_trap2b"

# Define as variáveis de entrada
A=10
B=20
N=1410065408

echo "Compilando o código otimizado (reduction)..."
# A flag -lm garante a linkagem com <math.h>
gcc -g -Wall -fopenmp -o $EXEC $SOURCE -lm

# Verifica se a compilação foi bem-sucedida
if [ $? -ne 0 ]; then
    echo "Erro durante a compilação. Abortando."
    exit 1
fi

echo "Compilação concluída com sucesso!"
echo "---------------------------------------------------"

echo "Testando com 1 thread (5 execuções para extração da mediana)..."
for i in {1..5}; do
    echo "Execução $i (1 thread):"
    echo "$A $B $N" | ./$EXEC 1
    echo "- - -"
done
echo "---------------------------------------------------"

echo "Testando com 2 threads (5 execuções para extração da mediana)..."
for i in {1..5}; do
    echo "Execução $i (2 threads):"
    echo "$A $B $N" | ./$EXEC 2
    echo "- - -"
done
echo "---------------------------------------------------"
echo "Pronto! Para achar a mediana, basta ordenar os 5 tempos de cada bateria"
echo "do menor para o maior e escolher o 3º valor."