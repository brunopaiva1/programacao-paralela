#!/bin/bash

# Define cores para destacar as mensagens no terminal
GREEN='\033[1;32m'
RED='\033[1;31m'
NC='\033[0m' # Sem Cor

make clean

make

# Verifica se a compilação foi bem-sucedida
if [ $? -eq 0 ]; then
    echo "=============================================================="
    
    # Executa o programa e guarda a saída no terminal e num ficheiro
    ./lru_experimento | tee saida_lru.txt
    
    echo "=============================================================="
else
    echo -e "${RED}Erro: A compilação falhou. Verifica o teu ficheiro lru_competitividade.cpp.${NC}"
fi