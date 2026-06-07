#!/bin/bash
make clean
make

BASE_SIZE=16000000000

for threads in 1 2 4 8 16; do
    # size=$(( BASE_SIZE * threads ))
    ./trapezio $threads $size
done