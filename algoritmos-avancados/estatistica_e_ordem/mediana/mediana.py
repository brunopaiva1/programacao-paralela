import random

class Cidade:
    def __init__(self, id_cidade, x, y, peso):
        self.id = id_cidade
        self.x = x
        self.y = y
        self.peso = peso

def quick_select_ponderado(pontos, alvo):
    if len(pontos) == 1:
        return pontos[0][0]

    pivo = random.choice(pontos)[0]
    
    menores, iguais, maiores = [], [], []
    peso_menores, peso_iguais = 0, 0

    for coord, peso in pontos:
        if coord < pivo:
            menores.append((coord, peso))
            peso_menores += peso
        elif coord == pivo:
            iguais.append((coord, peso))
            peso_iguais += peso
        else:
            maiores.append((coord, peso))

    if peso_menores >= alvo:
        return quick_select_ponderado(menores, alvo)
    elif peso_menores + peso_iguais >= alvo:
        return pivo
    else:
        return quick_select_ponderado(maiores, alvo - peso_menores - peso_iguais)

def resolver_agencia_postal(cidades):
    # print("=" * 55)
    # print("   QUESTÃO 3: LOCALIZAÇÃO ÓTIMA (MEDIANA PONDERADA)")
    # print("=" * 55)
    
    for c in cidades:
        print(f"Cidade {c.id}: Pos({c.x}, {c.y}) | População: {c.peso}")
    
    peso_total = sum(c.peso for c in cidades)
    alvo = peso_total / 2.0
    
    pontos_x = [(c.x, c.peso) for c in cidades]
    pontos_y = [(c.y, c.peso) for c in cidades]
    
    x_otimo = quick_select_ponderado(pontos_x, alvo)
    y_otimo = quick_select_ponderado(pontos_y, alvo)
    
    print("-" * 55)
    print(f"Peso Total (W): {peso_total} | Alvo (W/2): {alvo}")
    print(f"X Ótimo: {x_otimo}")
    print(f"Y Ótimo: {y_otimo}")
    print(f"\nRESULTADO: Ponto ideal da agência em ({x_otimo}, {y_otimo})")
    # print("=" * 55)

if __name__ == "__main__":
    lista_cidades = [
        Cidade(1, 1.0, 8.0, 450000),
        Cidade(2, 10.0, 2.0, 450000),
        Cidade(3, 5.0, 5.0, 50000)
    ]
    resolver_agencia_postal(lista_cidades)