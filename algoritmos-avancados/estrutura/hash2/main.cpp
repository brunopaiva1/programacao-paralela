#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include <algorithm>

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i = i + 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int nextPrime(int n) {
    int prime = n;
    while (true) {
        prime++;
        if (isPrime(prime)) return prime;
    }
}

int prevPrime(int n) {
    int prime = n;
    while (true) {
        prime--;
        if (isPrime(prime)) return prime;
    }
}

class LinearProbingHash {
private:
    enum State { EMPTY, OCCUPIED, DELETED };
    std::vector<int> table;
    std::vector<State> state;
    int capacity;
    int numElements;

    int hash1(int key) { return key % capacity; }

    void rehash() {
        int oldCapacity = capacity;
        capacity = capacity * 2;
        
        std::vector<int> oldTable = table;
        std::vector<State> oldState = state;
        
        table.assign(capacity, 0);
        state.assign(capacity, EMPTY);
        numElements = 0;
        
        for (int i = 0; i < oldCapacity; i++) {
            if (oldState[i] == OCCUPIED) {
                insert(oldTable[i]);
            }
        }
    }

public:
    LinearProbingHash(int size) : table(size), state(size, EMPTY), capacity(size), numElements(0) {}

    void insert(int key) {
        if ((float)numElements / capacity >= 0.75) {
            rehash();
        }

        int index = hash1(key);
        
        while (state[index] == OCCUPIED) {
            if (table[index] == key) return;
            index = (index + 1) % capacity;
        }
        
        table[index] = key;
        state[index] = OCCUPIED;
        numElements++;
    }

    bool search(int key) {
        int index = hash1(key);
        int startIndex = index;

        while (state[index] != EMPTY) {
            if (state[index] == OCCUPIED && table[index] == key) return true;
            index = (index + 1) % capacity;
            if (index == startIndex) break;
        }
        return false;
    }
};

class DoubleHashingHash {
private:
    enum State { EMPTY, OCCUPIED, DELETED };
    std::vector<int> table;
    std::vector<State> state;
    int capacity;
    int numElements;
    int prime; 

    int hash1(int key) { return key % capacity; }
    int hash2(int key) { return prime - (key % prime); }

    void rehash() {
        int oldCapacity = capacity;
        capacity = nextPrime(capacity * 2);
        prime = prevPrime(capacity); 
        
        std::vector<int> oldTable = table;
        std::vector<State> oldState = state;
        
        table.assign(capacity, 0);
        state.assign(capacity, EMPTY);
        numElements = 0;
        
        for (int i = 0; i < oldCapacity; i++) {
            if (oldState[i] == OCCUPIED) {
                insert(oldTable[i]);
            }
        }
    }

public:
    DoubleHashingHash(int size) : table(size), state(size, EMPTY), capacity(size), numElements(0) {
        prime = prevPrime(capacity); 
    }

    void insert(int key) {
        if ((float)numElements / capacity >= 0.75) {
            rehash();
        }

        int index = hash1(key);
        
        if (state[index] == OCCUPIED) {
            int step = hash2(key); 
            
            while (state[index] == OCCUPIED) {
                if (table[index] == key) return;
                index = (index + step) % capacity;
            }
        }
        
        table[index] = key;
        state[index] = OCCUPIED;
        numElements++;
    }

    bool search(int key) {
        int index = hash1(key);
        
        if (state[index] != EMPTY && (state[index] == DELETED || table[index] != key)) {
            int step = hash2(key);
            int startIndex = index;
            
            while (state[index] != EMPTY) {
                if (state[index] == OCCUPIED && table[index] == key) return true;
                index = (index + step) % capacity; 
                if (index == startIndex) break;
            }
        } else if (state[index] == OCCUPIED && table[index] == key) {
            return true;
        }
        
        return false;
    }
};

int main() {
    int TABLE_SIZE = 100003; 
    
    std::vector<int> tamanhos = {1000000, 5000000, 10000000}; 
    std::mt19937 rng(42);

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Tam_Tabela Inicial = " << TABLE_SIZE << " (Primo)\n";
    std::cout << "N        | Estrutura    | Insercao (s) | Busca Erro (s)\n";

    for (int n : tamanhos) {
        std::vector<int> dados(n);
        for(int i = 0; i < n; i++) dados[i] = i * 13; 
        std::shuffle(dados.begin(), dados.end(), rng);

        std::vector<int> alvos_erro(10000);
        for(int i = 0; i < 10000; i++) alvos_erro[i] = (i * 17) + 1; 

        LinearProbingHash linearHash(TABLE_SIZE);
        DoubleHashingHash doubleHash(TABLE_SIZE);

        auto t1 = std::chrono::high_resolution_clock::now();
        for(int x : dados) linearHash.insert(x);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto d_ins_lin = std::chrono::duration<double>(t2 - t1).count();

        t1 = std::chrono::high_resolution_clock::now();
        volatile int enc_lin = 0; 
        for(int x : alvos_erro) if (linearHash.search(x)) enc_lin++;
        t2 = std::chrono::high_resolution_clock::now();
        auto d_bus_lin = std::chrono::duration<double>(t2 - t1).count();

        t1 = std::chrono::high_resolution_clock::now();
        for(int x : dados) doubleHash.insert(x);
        t2 = std::chrono::high_resolution_clock::now();
        auto d_ins_doub = std::chrono::duration<double>(t2 - t1).count();

        t1 = std::chrono::high_resolution_clock::now();
        volatile int enc_doub = 0;
        for(int x : alvos_erro) if (doubleHash.search(x)) enc_doub++;
        t2 = std::chrono::high_resolution_clock::now();
        auto d_bus_doub = std::chrono::duration<double>(t2 - t1).count();

        std::cout << n << "  | Sond. Linear | " << d_ins_lin << "     | " << d_bus_lin << "\n";
        std::cout << n << "  | Hash. Duplo  | " << d_ins_doub << "     | " << d_bus_doub << "\n";
    }

    return 0;
}