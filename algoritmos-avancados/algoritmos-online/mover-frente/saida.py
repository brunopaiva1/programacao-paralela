import matplotlib.pyplot as plt
import re
import os
import sys

# Nome do ficheiro gerado pelo script bash
filename = 'saida_mtf.txt'

# Verifica se o ficheiro do C++ existe
if not os.path.exists(filename):
    print(f"Erro: O ficheiro '{filename}' não foi encontrado.")
    print("Por favor, executa primeiro o teu código C++ guardando a saída:")
    print("Ex: ./mtf_experimento > saida_mtf.txt")
    sys.exit(1)

print(f"A ler dados do ficheiro C++: {filename}...")

# Expressões Regulares para extrair os números das linhas do C++
# Procura linhas com o formato: "N = 1000 | ... | Taxa = 1.74"
padrao_N = re.compile(r"N\s*=\s*(\d+).*?Taxa\s*=\s*([\d.]+)")
# Procura linhas com o formato: "n_size = 10 | ... | Taxa = 3.45"
padrao_n_size = re.compile(r"n_size\s*=\s*(\d+).*?Taxa\s*=\s*([\d.]+)")

# Estruturas para guardar os dados
cenario1_N, cenario1_Taxa = [], []
cenario2_N, cenario2_Taxa = [], []
cenario3_n_size, cenario3_Taxa = [], []

# Máquina de estados para distinguir o Cenário 1 (Aleatório) do Cenário 2 (Pior Caso Fixo)
# Como ambos usam "N =", percebemos que o Cenário 2 começou quando o N volta a um número pequeno
bloco_atual = 1 

with open(filename, 'r') as f:
    for line in f:
        # Tenta casar com as linhas de N (Cenários 1 e 2)
        match_N = padrao_N.search(line)
        if match_N:
            n_val = int(match_N.group(1))
            taxa_val = float(match_N.group(2))
            
            # Se o N atual for menor que o anterior, significa que o C++ começou um novo laço (Cenário 2)
            if len(cenario1_N) > 0 and n_val < cenario1_N[-1] and bloco_atual == 1:
                bloco_atual = 2
                
            if bloco_atual == 1:
                cenario1_N.append(n_val)
                cenario1_Taxa.append(taxa_val)
            else:
                cenario2_N.append(n_val)
                cenario2_Taxa.append(taxa_val)
                
        # Tenta casar com as linhas de n_size (Cenário 3)
        match_n_size = padrao_n_size.search(line)
        if match_n_size:
            n_size_val = int(match_n_size.group(1))
            taxa_val = float(match_n_size.group(2))
            cenario3_n_size.append(n_size_val)
            cenario3_Taxa.append(taxa_val)

if not cenario1_N or not cenario3_n_size:
    print("Erro: Não foi possível extrair dados suficientes. O formato de saída mudou?")
    sys.exit(1)

print("Dados extraídos com sucesso! A desenhar gráficos...")

# ==========================================
# GRÁFICO 1: Cenário Aleatório
# ==========================================
plt.figure(figsize=(9, 5))
plt.plot(cenario1_N, cenario1_Taxa, marker='o', label='MTF / Ótimo (média)', color='tab:blue')
plt.axhline(4, color='r', linestyle='--', label='Limite teórico = 4')
plt.title('Taxa de competitividade do algoritmo Mover para a Frente (Uniforme)')
plt.xlabel('Número de acessos (N)')
plt.ylabel('Taxa média de competitividade')
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend(loc='center right')
plt.ylim(1.0, 4.2)
plt.tight_layout()
plt.savefig("grafico1_cpp.png")
plt.close()

# ==========================================
# GRÁFICO 2: Pior Caso Induzido (N fixo)
# ==========================================
plt.figure(figsize=(9, 5))
plt.plot(cenario2_N, cenario2_Taxa, marker='o', label='MTF / Ótimo (pior caso)', color='orange')
plt.axhline(4, color='r', linestyle='--', label='Limite teórico = 4')
plt.title('Taxa de competitividade do algoritmo Mover para a Frente (Pior Caso Fixo)')
plt.xlabel('Número de acessos (N)')
plt.ylabel('Taxa de competitividade')
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend(loc='center right')
plt.ylim(2.5, 4.2)
plt.tight_layout()
plt.savefig("grafico2_cpp.png")
plt.close()

# ==========================================
# GRÁFICO 3: Prova Assintótica (Escala Log)
# ==========================================
plt.figure(figsize=(9, 5))
plt.plot(cenario3_n_size, cenario3_Taxa, marker='o', label='Razão (MTF / OPT) no caso cíclico', color='tab:blue')
plt.axhline(4, color='r', linestyle='--', label='Limite teórico = 4')
plt.title('Como a razão se comporta no caso cíclico (adversário clássico)')
plt.xlabel('Tamanho da lista n (escala log)')
plt.ylabel('Razão média C_MTF / C_OPT')
plt.xscale('log') # Eixo X em escala logarítmica
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend(loc='lower right')
plt.ylim(2.5, 4.2)
plt.tight_layout()
plt.savefig("grafico3_cpp.png")
plt.close()

print("Pronto! Gráficos gerados com base na saída do teu C++: grafico1_cpp.png, grafico2_cpp.png e grafico3_cpp.png")