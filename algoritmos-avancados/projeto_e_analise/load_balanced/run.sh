#!/bin/bash

cd "$(dirname "$0")"


make clean
make

if [ $? -eq 0 ]; then
    ./load_balanced
else
    echo "Erro na compilação!"
    exit 1
fi