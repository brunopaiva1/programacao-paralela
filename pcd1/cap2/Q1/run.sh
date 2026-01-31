#!/bin/bash

make
make -j

echo "    n |     p |      Speedup |   Eficiência"
echo "------------------------------------------"

for ((n=10; n<=320; n*=2))
do
    for ((p=1; p<=128; p*=2))
    do
        ./saida.exe $n $p
    done
    echo "------------------------------------------"
done
