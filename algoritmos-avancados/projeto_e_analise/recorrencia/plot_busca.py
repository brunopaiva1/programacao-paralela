import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def plot_benchmark(csv_file):
    try:
        df = pd.read_csv(csv_file)
    except:
        return

    plt.figure(figsize=(10, 6))

    plt.plot(df['n'], df['tempo_ns'], label='Tempo Medido (Hardware Real)', 
             color='tab:blue', marker='o', linewidth=2)

    constante_escala = df['tempo_ns'].iloc[0] / np.log2(df['n'].iloc[0])
    curva_teorica = constante_escala * np.log2(df['n'])
    
    plt.plot(df['n'], curva_teorica, label='Curva Teórica $\Theta(\log n)$', 
             color='tab:orange', linestyle='--', linewidth=2)

    plt.xscale('log', base=2)
    
    plt.axvline(x=2**20, color='gray', linestyle=':', alpha=0.7)
    plt.text(2**20 * 1.2, df['tempo_ns'].max() * 0.5, 
             'Divergência de Cache (L3 Miss)\nLatência de RAM domina o custo', 
             color='gray', fontsize=10)

    plt.xlabel('Tamanho do Vetor (N)')
    plt.ylabel('Tempo de Execução (Nanossegundos)')
    plt.title('Análise de Recorrência: Busca Binária Recursiva')
    plt.legend()
    plt.grid(True, which="both", ls="-", alpha=0.2)
    plt.tight_layout()
    plt.savefig('grafico_busca.png')
    print("Gráfico 'grafico_busca.png' salvo com sucesso!")

if __name__ == "__main__":
    plot_benchmark('benchmark_busca.csv')