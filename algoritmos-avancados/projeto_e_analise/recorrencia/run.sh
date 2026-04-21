#!/bin/bash

cd "$(dirname "$0")"

make clean
make

if [ $? -eq 0 ]; then
    ./bench_busca
    
    if [ -f "benchmark_busca.csv" ]; then
        python3 plot_busca.py
    else
        echo "ERRO: O arquivo benchmark_busca.csv não foi gerado."
        exit 1
    fi
else
    echo "ERRO: Falha na compilação."
    exit 1
fi