#!/bin/bash
cd "$(dirname "$0")"

make clean
make

if [ $? -eq 0 ]; then
    echo -e "\n=== Executando C++ ==="
    ./bench_quicksort
    
    if [ -f "benchmark_quicksort.csv" ]; then
        echo -e "\n=== Gerando Gráficos (Python) ==="
        python3 plot_quicksort.py
        echo "Sucesso! O arquivo grafico_quicksort.png foi gerado."
    fi
else
    exit 1
fi