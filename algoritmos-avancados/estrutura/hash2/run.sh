#!/bin/bash

clear

make clean
make

if [ $? -eq 0 ]; then
    echo " "
    
    ./benchmark_hash
    
    echo " "
    echo "Operação finalizado!"
else
    echo " "
    echo "ERRO: A compilação falhou."
fi