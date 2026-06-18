#!/bin/bash

GREEN='\033[1;32m'
RED='\033[1;31m'
NC='\033[0m' 

echo -e "${GREEN}[1/3] A limpar ficheiros antigos...${NC}"
make clean

echo -e "${GREEN}[2/3] A compilar o código C++ com otimização máxima (-O3)...${NC}"
make

if [ $? -eq 0 ]; then
    echo -e "${GREEN}[3/3] Compilação concluída! A executar o experimento...${NC}"
    echo "=============================================================="
    
    ./mtf_experimento | tee saida_mtf.txt
    
    echo "=============================================================="
    echo -e "${GREEN}Experimento finalizado com sucesso!${NC}"
    echo -e "Os dados foram também guardados no ficheiro: ${GREEN}saida_mtf.txt${NC}"
else
    echo -e "${RED}Erro: A compilação falhou. Verifica o teu ficheiro .cpp.${NC}"
fi