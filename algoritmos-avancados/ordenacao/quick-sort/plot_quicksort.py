import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("benchmark_quicksort.csv")

plt.figure(figsize=(14, 6))
plt.suptitle("Análise Assintótica: Quicksort Padrão vs Aleatório", fontsize=16, fontweight='bold')

colors = {'Padrão': 'tab:red', 'Aleatório': 'tab:blue'}
markers = {'Padrão': 'o', 'Aleatório': 's'}
linestyles = {'Padrão': '--', 'Aleatório': '-'}

plt.subplot(1, 2, 1)
df_avg = df[df['case'] == 'average']
for alg in df_avg['algorithm'].unique():
    data = df_avg[df_avg['algorithm'] == alg]
    plt.loglog(data['n'], data['time_ms'], marker=markers[alg], color=colors[alg], 
               linestyle=linestyles[alg], linewidth=2, label=alg)

plt.title('Caso Médio (Vetor Aleatório)', fontsize=14)
plt.xlabel('Tamanho do Vetor (N) - Escala Log', fontsize=12)
plt.ylabel('Tempo de Execução (ms) - Escala Log', fontsize=12)
plt.legend(loc='upper left')
plt.grid(True, which="both", ls=":", alpha=0.7)

plt.subplot(1, 2, 2)
df_worst = df[df['case'] == 'worst']
for alg in df_worst['algorithm'].unique():
    data = df_worst[df_worst['algorithm'] == alg]
    plt.loglog(data['n'], data['time_ms'], marker=markers[alg], color=colors[alg], 
               linestyle=linestyles[alg], linewidth=2, label=alg)

plt.title('Pior Caso (Entrada Adversária/Ordenada)', fontsize=14)
plt.xlabel('Tamanho do Vetor (N) - Escala Log', fontsize=12)
plt.ylabel('Tempo de Execução (ms) - Escala Log', fontsize=12)
plt.legend(loc='upper left')
plt.grid(True, which="both", ls=":", alpha=0.7)

plt.tight_layout()
plt.savefig('grafico_quicksort.png', dpi=300)
print("Gráfico Log-Log gerado com sucesso!")