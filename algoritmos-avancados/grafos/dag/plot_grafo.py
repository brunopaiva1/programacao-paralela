import networkx as nx
import matplotlib.pyplot as plt

# Cria o Grafo Direcionado
G = nx.DiGraph()

# Nomes exatos que você definiu no seu C++
nomes = {
    0: "Revisão\nBibliográfica",
    1: "Execução dos\nExperimentos",
    2: "Análise dos\nResultados",
    3: "Escrita da\nMetodologia",
    4: "Escrita da\nIntrodução",
    5: "Escrita dos\nResultados\ne Discussão",
    6: "Revisão",
    7: "Submissão\nfinal"
}

# Suas arestas com os atalhos para a Revisão (6)
arestas = [
    (0, 1), (1, 2), (2, 3), (3, 4), 
    (4, 5), (5, 6), (4, 6), (3, 6), (6, 7)
]
G.add_edges_from(arestas)

# Coordenadas ajustadas para evitar que as flechas se cruzem
pos = {
    0: (0, 0),
    1: (1, 0),
    2: (2, 0),
    3: (3, 0),
    4: (4, 1),    # Elevado para formar um arco superior
    5: (5, 1),    # Elevado para formar um arco superior
    6: (6, 0),    # Retorna para o eixo principal (recebendo o 3 e o 4)
    7: (7, 0)
}

# Configuração da tela
plt.figure(figsize=(15, 5))

# Desenha as arestas e nós
nx.draw(G, pos, with_labels=False, node_size=4000, node_color="#4fc3f7", 
        edge_color="#757575", arrows=True, arrowsize=20, width=1.5)

# Insere os textos
labels = {n: f"{n}\n{nomes[n]}" for n in G.nodes()}
nx.draw_networkx_labels(G, pos, labels, font_size=9, font_weight="bold", font_color="black")

# Finaliza o plot
plt.title("DAG - Ordem Topológica da Escrita do Artigo", fontsize=15, fontweight="bold", pad=20)
plt.axis("off")
plt.tight_layout()

# Salva a imagem
plt.savefig("dag_artigo_final.png", dpi=300, bbox_inches='tight')
print("Imagem 'dag_artigo_final.png' gerada com sucesso!")

plt.show()