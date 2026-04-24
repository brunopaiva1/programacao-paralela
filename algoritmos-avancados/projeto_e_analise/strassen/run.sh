#!/bin/bash

cd "$(dirname "$0")"

echo "=== Iniciando Pipeline de Benchmark (Strassen) ==="

make clean
make

if [ $? -eq 0 ]; then
    echo "=== Executando o Benchmark ==="
    ./bench_strassen
    
    echo "=== Processo Finalizado ==="
    echo "Verifique o arquivo .csv gerado na sua pasta."
else
    echo "ERRO: A compilação falhou. Verifique seu código C++."
    exit 1
fi