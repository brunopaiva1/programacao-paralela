#!/bin/bash

clear

make clean
make

if [ $? -eq 0 ]; then
    
    ./estruturas
    
    echo " "
    echo "Execução finalizada!"
else
    echo " "
    echo "ERRO: A compilação falhou. Verifique o seu código estruturas.cpp."
fi