#!/bin/bash

PREFIX=$HOME/home/bruno/programacao-paralela/openmp/Monte_Carlo/ ; wait

cd $PREFIX ; wait

make -j ; wait

./main.o 8 30000000