#!/bin/bash

cd "$(dirname "$0")"


make clean
make

if [ $? -eq 0 ]; then
    
    ./selecao
    
else
    echo "Erro: Falha na compilação do código selecao.cpp."
    exit 1
fi