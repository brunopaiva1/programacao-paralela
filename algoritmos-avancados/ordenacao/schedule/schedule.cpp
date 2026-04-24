// 7. Implemente as funções da seção 6.5 (Priority queues) do livro do
// Cormen 4th Ed. em sua linguagem favorita e proponha um exemplo de
// uso com uma demonstração.

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <string>

using namespace std;

struct Node {
    int prioridade;
    int pid;
    string nome;

    Node(int p, int id, string n = "") 
        : prioridade(p), pid(id), nome(std::move(n)) {}
};

class Heap {
private:
    vector<Node> v;
    size_t size_heap;
    unordered_map<int, int> pos;

    void swapElements(int i, int j) {
        swap(v[i], v[j]);
        pos[v[i].pid] = i;
        pos[v[j].pid] = j;
    }

    void maxHeapify(int i) {
        int largest = i;
        int left = i << 1;
        int right = (i << 1) + 1;

        if (left <= (int)size_heap && v[left].prioridade > v[largest].prioridade)
            largest = left;
        if (right <= (int)size_heap && v[right].prioridade > v[largest].prioridade)
            largest = right;

        if (largest != i) {
            swapElements(i, largest);
            maxHeapify(largest);
        }
    }

public:
    Heap() {
        v.emplace_back(Node(-1, -1));
        size_heap = 0;
    }

    bool isEmpty() const { return size_heap == 0; }
    int getSize() const { return size_heap; }

    void insert(int key, int id, string nome) {
        if (pos.find(id) != pos.end()) {
            throw invalid_argument("PID ja existe no heap");
        }
        
        v.push_back(Node(key, id, nome));
        ++size_heap;
        pos[id] = size_heap;

        int i = size_heap;
        while (i > 1 && v[i >> 1].prioridade < v[i].prioridade) {
            swapElements(i, i >> 1);
            i = i >> 1;
        }
    }

    Node maximum() const {
        if (isEmpty()) throw runtime_error("Heap vazio");
        return v[1];
    }

    Node extractMax() {
        if (isEmpty()) throw runtime_error("Heap vazio");
        
        Node maxNode = v[1];
        swapElements(1, size_heap);
        
        pos.erase(maxNode.pid);
        v.pop_back();
        --size_heap;

        if (size_heap > 0) {
            maxHeapify(1);
        }

        return maxNode;
    }

    void increaseKey(int id, int novaChave) {
        if (pos.find(id) == pos.end()) throw runtime_error("PID nao encontrado");

        int i = pos[id];
        if (novaChave < v[i].prioridade) throw invalid_argument("Nova chave e menor que a atual");

        v[i].prioridade = novaChave;

        while (i > 1 && v[i >> 1].prioridade < v[i].prioridade) {
            swapElements(i, i >> 1);
            i = i >> 1;
        }
    }

    void printHeap() const {
        for (int i = 1; i <= (int)size_heap; ++i) {
            cout << "(PID:" << v[i].pid << ", Prio:" << v[i].prioridade << ") ";
        }
        cout << "\n";
    }
};

class Scheduler {
private:
    Heap heap;

public:
    void addProcess(int pid, int prioridade, const string &nome) {
        heap.insert(prioridade, pid, nome);
    }

    void boostPriority(int pid, int novaPrioridade) {
        heap.increaseKey(pid, novaPrioridade);
    }

    void run() {
        if (heap.isEmpty()) {
            cout << "Nenhum processo para executar.\n";
            return;
        }

        Node p = heap.extractMax();
        cout << "Executando processo PID:" << p.pid
             << " (" << p.nome << ") com prioridade "
             << p.prioridade << "\n";
    }

    bool hasProcesses() const { return !heap.isEmpty(); }
};

int main() {
    Scheduler escalonador;

    escalonador.addProcess(101, 3, "Editor de Texto");
    escalonador.addProcess(102, 5, "Navegador Web");
    escalonador.addProcess(103, 1, "Atualizacao em segundo plano");
    escalonador.addProcess(104, 4, "Compilacao de codigo");

    escalonador.run();
    escalonador.run();

    escalonador.boostPriority(103, 6);

    while (escalonador.hasProcesses()) {
        escalonador.run();
    }

    return 0;
}