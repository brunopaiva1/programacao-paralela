#!/bin/bash

cd "$(dirname "$0")"

make clean
make

if [ $? -eq 0 ]; then
    echo ""
    ./schedule
else
    exit 1
fi