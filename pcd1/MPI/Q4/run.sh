#!/bin/bash

make

if [ $? -ne 0 ]; then
    echo "Erro na compilação!"
    exit 1
fi

N_PROCESSOS=4

mpirun -np $N_PROCESSOS ./saida.exe