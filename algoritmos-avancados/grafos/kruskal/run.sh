#!/bin/bash
clear

echo "================================================="
echo "Compilando Benchmark de Kruskal vs Prim (-O3)..."
echo "================================================="
make clean
make

if [ $? -eq 0 ]; then
    echo " "
    echo "Compilação concluída com sucesso! Iniciando os testes..."
    echo " "
    ./mst_benchmark
else
    echo "Erro na compilação."
fi