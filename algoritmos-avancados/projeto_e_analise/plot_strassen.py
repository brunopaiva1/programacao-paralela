import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.ticker import ScalarFormatter # <-- Nova importação necessária

def plot_strassen(csv_file):
    try:
        df = pd.read_csv(csv_file)
    except FileNotFoundError:
        print("Arquivo CSV não encontrado.")
        return

    plt.figure(figsize=(10, 6))

    plt.plot(df['Size'], df['Conventional'], label='Convencional', 
             color='tab:red', marker='o', linestyle='-', linewidth=2)
    plt.plot(df['Size'], df['Strassen'], label='Strassen', 
             color='tab:blue', marker='s', linestyle='--', linewidth=2)

    plt.xscale('log', base=2)
    plt.yscale('log', base=10)

    ax = plt.gca() 
    formatter = ScalarFormatter()
    formatter.set_scientific(False) 
    ax.yaxis.set_major_formatter(formatter)

    plt.axvline(x=512, color='gray', linestyle=':', alpha=0.7)
    
    plt.text(550, 50, 'Crossover Threshold\n(Convencional perde força)', 
             color='gray', fontsize=10)

    plt.xlabel('Dimensão da Matriz (N x N)')
    plt.ylabel('Tempo de Execução (ms)')
    plt.title('Benchmark: Multiplicação Convencional vs Strassen')
    plt.grid(True, which="both", ls="-", alpha=0.2)
    plt.legend()
    plt.tight_layout()
    
    plt.savefig('strassen_resultado.png', dpi=300)
    print("Gráfico 'strassen_resultado.png' salvo com sucesso!")

if __name__ == "__main__":
    plot_strassen('strassen_benchmark.csv')