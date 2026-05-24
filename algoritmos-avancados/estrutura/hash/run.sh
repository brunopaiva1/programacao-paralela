#!/bin/bash

clear

make clean
make

if [ $? -eq 0 ]; then
    echo " "
    echo "Compilação concluída com sucesso com a flag -O3."
    echo "Iniciando os testes..."
    echo " "
    
    ./benchmark_hash
    
    echo " "
    echo "Benchmark finalizado!"
else
    echo " "
    echo "ERRO: A compilação falhou."
fi