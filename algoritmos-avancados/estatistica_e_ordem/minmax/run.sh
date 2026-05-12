#!/bin/bash

cd "$(dirname "$0")"

echo "=== Pipeline de Execução: Mínimo e Máximo Simultâneos ==="

make clean
make

if [ $? -eq 0 ]; then
    echo -e "\n=== Iniciando Benchmark (Vetor de 500M) ===\n"
    
    ./minmax
    
    echo -e "\n=== Execução Finalizada ==="
else
    echo "Erro: Falha na compilação do código minmax.cpp."
    exit 1
fi