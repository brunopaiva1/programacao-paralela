#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

struct Ponto {
    double coord;
    double peso;
};

double mediana_ponderada(std::vector<Ponto> pontos) {
    double peso_total = 0;
    for (const auto& p : pontos) peso_total += p.peso;
    double alvo = peso_total / 2.0;

    std::sort(pontos.begin(), pontos.end(), [](Ponto a, Ponto b) {
        return a.coord < b.coord;
    });

    double soma_acumulada = 0;
    for (const auto& p : pontos) {
        soma_acumulada += p.peso;
        if (soma_acumulada >= alvo) return p.coord;
    }
    return pontos.back().coord;
}

int main() {
    struct Cidade { int id; double x, y, peso; };
    std::vector<Cidade> cidades = {
        {1, 1.0, 8.0, 450000},
        {2, 10.0, 2.0, 450000},
        {3, 5.0, 5.0, 50000}
    };

    for (const auto& c : cidades) {
        std::cout << "Cidade " << c.id << ":" << std::endl;
        std::cout << "  Coordenadas: (" << c.x << ", " << c.y << ")" << std::endl;
        std::cout << "  Habitantes : " << (int)c.peso << "\n" << std::endl;
    }

    std::vector<Ponto> cx, cy;
    for (const auto& c : cidades) {
        cx.push_back({c.x, c.peso});
        cy.push_back({c.y, c.peso});
    }


    double x_otimo = mediana_ponderada(cx);
    std::cout << "  X otimo encontrado: " << x_otimo << std::endl;

    double y_otimo = mediana_ponderada(cy);
    std::cout << "  Y otimo encontrado: " << y_otimo << std::endl;

    std::cout << "\n>>> RESULTADO FINAL <<<" << std::endl;
    std::cout << "A localizacao otima (Distancia Manhattan) e: (" << x_otimo << ", " << y_otimo << ")" << std::endl;

    return 0;
}