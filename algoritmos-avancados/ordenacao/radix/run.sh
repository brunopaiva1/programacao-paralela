#!/bin/bash

# Garante que o script rode na pasta onde ele está localizado
cd "$(dirname "$0")"

echo "=== Pipeline: Radix Sort vs Counting Sort ==="

# 1. Limpa e compila
make clean
make

# 2. Executa o C++ e depois o Python
if [ $? -eq 0 ]; then
    echo -e "\n=== Executando Benchmark em C++ ==="
    ./bench_radix
    
    if [ -f "benchmark_radix.csv" ]; then
        echo -e "\n=== Gerando Gráficos com Python ==="
        python3 plot_radix.py
        echo -e "\n=== Pipeline Finalizado com Sucesso! ==="
    else
        echo "ERRO: O arquivo benchmark_radix.csv não foi gerado."
        exit 1
    fi
else
    echo "ERRO: Falha na compilação."
    exit 1
fi