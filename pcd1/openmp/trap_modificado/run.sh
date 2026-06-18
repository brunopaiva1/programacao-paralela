#!/bin/bash

# Define os nomes dos arquivos
SOURCE="omp_trap1.c"
EXEC="omp_trap1"

# Define as variáveis de entrada
A=10
B=20
N=1410065408

echo "Compilando o código..."
# A flag -lm é adicionada para garantir a correta linkagem da biblioteca math.h (<math.h>)
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