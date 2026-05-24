// 2. Implemente tabelas hash com encadeamento e usando endereçamento
// aberto. Realize experimentos para mostrar numericamente as vantagens
// e desvantagens de cada caso, considerando as operações de inserção,
// busca e remoção.


#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <random>
#include <iomanip>

// tabela hash com encadeamento
class ChainingHash {
private:
    std::vector<std::list<int>> table;
    int numElements;
    
    int hashFunction(int key) {
        return key % table.size();
    }

public:
    ChainingHash(int size) : table(size), numElements(0) {}

    void insert(int key) {
        int index = hashFunction(key);
        for (int k : table[index]) {
            if (k == key) return; 
        }
        table[index].push_front(key);
        numElements++;
    }

    bool search(int key) {
        int index = hashFunction(key);
        for (int k : table[index]) {
            if (k == key) return true;
        }
        return false;
    }

    void remove(int key) {
        int index = hashFunction(key);
        table[index].remove(key);
    }
};

// tabela hash com endereçamento aberto

class OpenAddressingHash {
private:
    enum State { EMPTY, OCCUPIED, DELETED };
    
    std::vector<int> table;
    std::vector<State> state;
    int capacity;
    int numElements;

    int hashFunction(int key) {
        return key % capacity;
    }

public:
    OpenAddressingHash(int size) : table(size), state(size, EMPTY), capacity(size), numElements(0) {}

    void insert(int key) {
        if (numElements == capacity) return; 

        int index = hashFunction(key);
        
        while (state[index] == OCCUPIED) {
            if (table[index] == key) return;
            index = (index + 1) % capacity;
        }
        
        table[index] = key;
        state[index] = OCCUPIED;
        numElements++;
    }

    bool search(int key) {
        int index = hashFunction(key);
        int startIndex = index;

        while (state[index] != EMPTY) {
            if (state[index] == OCCUPIED && table[index] == key) {
                return true;
            }
            index = (index + 1) % capacity;
            if (index == startIndex) break; 
        }
        return false;
    }

    void remove(int key) {
        int index = hashFunction(key);
        int startIndex = index;

        while (state[index] != EMPTY) {
            if (state[index] == OCCUPIED && table[index] == key) {
                state[index] = DELETED;
                numElements--;
                return;
            }
            index = (index + 1) % capacity;
            if (index == startIndex) break;
        }
    }
};

int main() {
    int TABLE_SIZE = 100000;
    std::vector<int> tamanhos = {50000, 80000, 95000, 99000}; 
    std::mt19937 rng(42);

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Tam_Tabela = " << TABLE_SIZE << "\n";
    std::cout << "N | Estrutura | Insercao (s) | Busca (s) | Remocao (s)\n";

    for (int n : tamanhos) {
        std::vector<int> dados(n);
        for(int i = 0; i < n; i++) dados[i] = i * 7;
        std::shuffle(dados.begin(), dados.end(), rng);

        std::vector<int> alvos_teste(10000);
        for(int i = 0; i < 10000; i++) alvos_teste[i] = dados[rng() % n];

        ChainingHash chainHash(TABLE_SIZE);
        OpenAddressingHash openHash(TABLE_SIZE);

        auto t1 = std::chrono::high_resolution_clock::now();
        for(int x : dados) chainHash.insert(x);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto d_ins_chain = std::chrono::duration<double>(t2 - t1).count();

        t1 = std::chrono::high_resolution_clock::now();
        for(int x : alvos_teste) chainHash.search(x);
        t2 = std::chrono::high_resolution_clock::now();
        auto d_bus_chain = std::chrono::duration<double>(t2 - t1).count();

        t1 = std::chrono::high_resolution_clock::now();
        for(int x : alvos_teste) chainHash.remove(x);
        t2 = std::chrono::high_resolution_clock::now();
        auto d_rem_chain = std::chrono::duration<double>(t2 - t1).count();

        t1 = std::chrono::high_resolution_clock::now();
        for(int x : dados) openHash.insert(x);
        t2 = std::chrono::high_resolution_clock::now();
        auto d_ins_open = std::chrono::duration<double>(t2 - t1).count();

        t1 = std::chrono::high_resolution_clock::now();
        for(int x : alvos_teste) openHash.search(x);
        t2 = std::chrono::high_resolution_clock::now();
        auto d_bus_open = std::chrono::duration<double>(t2 - t1).count();

        t1 = std::chrono::high_resolution_clock::now();
        for(int x : alvos_teste) openHash.remove(x);
        t2 = std::chrono::high_resolution_clock::now();
        auto d_rem_open = std::chrono::duration<double>(t2 - t1).count();

        std::cout << n << " | Chaining  | " << d_ins_chain << " | " << d_bus_chain << " | " << d_rem_chain << "\n";
        std::cout << n << " | Open Addr | " << d_ins_open  << " | " << d_bus_open  << " | " << d_rem_open  << "\n";
    }

    return 0;
}