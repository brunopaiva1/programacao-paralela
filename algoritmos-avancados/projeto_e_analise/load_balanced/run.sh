#!/bin/bash

cd "$(dirname "$0")"

echo "=== Benchmark de Balanceamento de Carga ==="

make clean
make

if [ $? -eq 0 ]; then
    echo -e "\n=== Resultados do Experimento ===\n"
    ./load_balanced
    echo -e "\n=== Simulação Finalizada ==="
else
    echo "Erro na compilação!"
    exit 1
fi