#!/bin/bash

PREFIX=$HOME/programacao-paralela/pcd1/openmp/ ; wait

cd $PREFIX ; wait

make -j ; wait

# gcc -fopenmp -o saida.exe Histograma.cpp ; wait