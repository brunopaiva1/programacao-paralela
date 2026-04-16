#!/bin/bash

# Nome dos arquivos
CPP_FILE="insersion.cpp"
EXE_FILE="bench"
CSV_FILE="dados.csv"
PY_FILE="script_grafico.py"

echo "Compilando o código C++..."
g++ -O3 $CPP_FILE -o $EXE_FILE

if [ $? -eq 0 ]; then
    echo "Executando benchmark e gerando $CSV_FILE..."
    ./$EXE_FILE > $CSV_FILE
    
    echo "Gerando gráfico com Python..."
    python3 $PY_FILE
    
    echo "Processo concluído! Imagem 'analise_desempenho.png' criada."
else
    echo "Erro na compilação!"
fi