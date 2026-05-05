import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("benchmark_radix.csv")

plt.figure(figsize=(14, 6))
plt.suptitle("Radix Sort vs Counting Sort (Análise de Gargalo de Memória)", fontsize=16, fontweight='bold')

colors = {'Counting Sort': 'tab:red', 'Radix Sort': 'tab:blue'}
markers = {'Counting Sort': 'o', 'Radix Sort': 's'}

plt.subplot(1, 2, 1)
df_small = df[df['cenario'] == 'Pequenos']
for alg in df_small['algorithm'].unique():
    data = df_small[df_small['algorithm'] == alg]
    plt.plot(data['n'], data['time_ms'], marker=markers[alg], color=colors[alg], linewidth=2, label=alg)

plt.title('Valores Pequenos (K_max = 1.000)', fontsize=14)
plt.xlabel('Tamanho do Vetor (N)', fontsize=12)
plt.ylabel('Tempo de Execução (ms)', fontsize=12)
plt.legend()
plt.grid(True, linestyle='--', alpha=0.7)

plt.subplot(1, 2, 2)
df_large = df[df['cenario'] == 'Grandes']
for alg in df_large['algorithm'].unique():
    data = df_large[df_large['algorithm'] == alg]
    plt.plot(data['n'], data['time_ms'], marker=markers[alg], color=colors[alg], linewidth=2, label=alg)

plt.title('Valores Gigantes (K_max = 100.000.000)', fontsize=14)
plt.xlabel('Tamanho do Vetor (N)', fontsize=12)
plt.ylabel('Tempo de Execução (ms)', fontsize=12)
plt.legend()
plt.grid(True, linestyle='--', alpha=0.7)

plt.tight_layout()
plt.savefig('grafico_radix.png', dpi=300)
print("Gráfico 'grafico_radix.png' salvo com sucesso!")