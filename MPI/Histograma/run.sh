#!/bin/bash

PREFIX=$HOME/Documentos/openmp/Q6 ; wait

cd $PREFIX ; wait

make -j ; wait

mpiexec -np 4 ./saida.o > histograma.txt

python3 main.py
