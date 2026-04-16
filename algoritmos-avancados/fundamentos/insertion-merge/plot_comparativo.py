import pandas as pd
import matplotlib.pyplot as plt

def plot_comparison(csv_file):
    try:
        df = pd.read_csv(csv_file)
    except:
        return

    plt.figure(figsize=(12, 7))
    
    styles = {
        ('insertion', 'melhor'): ('blue', ':'),
        ('insertion', 'medio'): ('blue', '-'),
        ('insertion', 'pior'): ('blue', '--'),
        ('merge', 'melhor'): ('red', ':'),
        ('merge', 'medio'): ('red', '-'),
        ('merge', 'pior'): ('red', '--')
    }

    for (algo, cenario), (color, ls) in styles.items():
        subset = df[(df['algo'] == algo) & (df['cenario'] == cenario)]
        plt.plot(subset['n'], subset['tempo_ns'], label=f"{algo} ({cenario})", 
                 color=color, linestyle=ls, marker='o', markersize=4)

    plt.xscale('log')
    plt.yscale('log')
    plt.xlabel('Tamanho da Entrada (n)')
    plt.ylabel('Tempo de Execução (ns)')
    plt.title('Comparativo: Insertion Sort vs Merge Sort (Todos os Casos)')
    plt.legend()
    plt.grid(True, which="both", ls="-", alpha=0.2)
    plt.tight_layout()
    plt.savefig('comparativo_algoritmos.png')
    plt.show()

if __name__ == "__main__":
    plot_comparison('dados_comparativos.csv')