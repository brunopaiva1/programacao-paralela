#!/bin/bash

CPP_FILE="insertion_merge.cpp"
EXE_FILE="bench_comparativo"
CSV_FILE="dados_comparativos.csv"
PY_FILE="plot_comparativo.py"

cd "$(dirname "$0")"

echo "--- Iniciando Benchmark de Algoritmos ---"

echo "[1/3] Compilando C++ com otimização -O3..."
g++ -O3 "$CPP_FILE" -o "$EXE_FILE"

if [ $? -eq 0 ]; then
    echo "[2/3] Executando testes e gerando CSV..."
    ./"$EXE_FILE" > "$CSV_FILE"
    
    echo "[3/3] Gerando gráficos com Python..."
    python3 "$PY_FILE"
    
    echo "--- Processo concluído com sucesso! ---"
    echo "Arquivos gerados: $CSV_FILE e comparativo_algoritmos.png"
else
    echo "ERRO: Falha na compilação do arquivo $CPP_FILE"
    exit 1
fi