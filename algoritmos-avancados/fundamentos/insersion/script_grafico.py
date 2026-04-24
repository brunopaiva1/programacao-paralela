import pandas as pd
import matplotlib.pyplot as plt
import sys

def plot_performance(csv_file):
    try:
        df = pd.read_csv(csv_file)
    except Exception as e:
        print(f"Erro ao ler CSV: {e}")
        return

    fig, ax1 = plt.subplots(figsize=(10, 6))

    color = 'tab:blue'
    ax1.set_xlabel('Tamanho da Entrada (n)')
    ax1.set_ylabel('Operações RAM (Teórico)', color=color)
    ax1.plot(df['n'], df['ram_ops'], label='Modelo RAM', color=color, marker='o', linestyle='--')
    ax1.tick_params(axis='y', labelcolor=color)
    ax1.set_xscale('log', base=2)
    ax1.set_yscale('log', base=10)

    ax2 = ax1.twinx()
    color = 'tab:red'
    ax2.set_ylabel('Tempo Real (ns)', color=color)
    ax2.plot(df['n'], df['real_ns'], label='Máquina Real', color=color, marker='x')
    ax2.tick_params(axis='y', labelcolor=color)
    ax2.set_yscale('log', base=10)

    plt.title('Divergência: Modelo RAM vs. Máquina Real (Insertion Sort)')
    fig.tight_layout()
    plt.savefig('analise_desempenho.png')
    print("Arquivo 'analise_desempenho.png' salvo com sucesso.")

if __name__ == "__main__":
    plot_performance('dados.csv')