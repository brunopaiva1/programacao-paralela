// 1. Implemente as estruturas de dados: 1) array ordenado, 2) lista encadeada
// não ordenada, e 3) árvore de busca binária balanceada (e.g., AVL,
// Red-Black trees). Em seguida, insira n elementos em cada estrutura de
// dados. Depois disso, considerando diferentes valores de n, compare os
// tempos de inserção e busca de cada uma.

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

// 1) Array ordenado
class SortedArray {
    private: 
        std:: vector<int> arr; 
    public:
        void insert(int val){
             arr.push_back(val);
             int j = arr.size() -2;

             while(j >= 0 && arr[j] > val){
                arr[j + 1] = arr[j];
                j--;
             }
             arr[j + 1] = val;
        }

        bool search(int val){
            int esq = 0;
            int dir = arr.size() - 1;

            while(esq <= dir){
                int meio = esq + (dir - esq) / 2;

                if(arr[meio] == val){
                    return true;
                }

                if(arr[meio] < val) {
                    esq = meio + 1;
                } else {
                    dir = meio - 1;
                }
            }

            return false;
        }
};

// 2) Lista encadeada não ordenada

struct NodeLista{
    int data;
    NodeLista* next;

    NodeLista(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    NodeLista* head;

public:
    LinkedList() : head(nullptr) {}

    void insert(int val){
        NodeLista* newNode = new NodeLista(val);
        newNode->next = head;
        head = newNode;
    }

    bool search(int val){
        NodeLista* curr = head;

        while(curr != nullptr){
            if(curr->data == val){
                return true;
            }

            curr = curr->next;
        }
        return false;
    }
};

// Árvore AVL

struct NodeAVL {
    int data, height;
    NodeAVL *left, *right;
    NodeAVL(int val) : data(val), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    NodeAVL* root;

    int height(NodeAVL* n) { return n ? n->height : 0; }
    int getBalance(NodeAVL* n) { return n ? height(n->left) - height(n->right) : 0; }

    NodeAVL* rightRotate(NodeAVL* y){
        NodeAVL* x = y->left;
        NodeAVL* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;
        return x;
    }

     NodeAVL* leftRotate(NodeAVL* x){
        NodeAVL* y = x->right;
        NodeAVL* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = std::max(height(x->left), height(y->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;
        return y;
    }

    NodeAVL* insertNode(NodeAVL* node, int val) {
        if(!node) return new NodeAVL(val);
        if(val < node->data) node->left = insertNode(node->left, val);
        else if(val > node->data) node->right = insertNode(node->right, val);
        else return node;

        node->height = 1 + std::max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if(balance > 1 && val < node->left->data) return rightRotate(node);
        if(balance < -1 && val > node->right->data) return leftRotate(node);
        if(balance > 1 && val > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if(balance < -1 && val < node->right->data){
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    bool searchNode(NodeAVL* node, int val) {
        if(!node) return false;
        if(node->data == val) return true;
        if(val < node->data) return searchNode(node->left, val);
        return searchNode(node->right, val);
    }
public:
    AVLTree() : root(nullptr){}
    void insert(int val) {root = insertNode(root, val);}
    bool search(int val) {return searchNode(root, val);}
};

int main(){

    std::vector<int> tamanhos = {1000, 5000, 10000, 20000};
    std::mt19937 rng(42);

    std::cout << "N | Estrutura | Inserção | Busca" << std::endl;

    for(int n : tamanhos){
        std::vector<int> dados(n);
        for(int i = 0; i < n; i++) dados[i] = i;
        shuffle(dados.begin(), dados.end(), rng);

        LinkedList lista;
        SortedArray arr;
        AVLTree avl;

        auto t1 = std::chrono::high_resolution_clock::now();
        for(int x : dados) lista.insert(x);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto d_ins_lista = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

        t1 = std::chrono::high_resolution_clock::now();
        for(int i=0; i<1000; i++) lista.search(rng() % n);
        t2 = std::chrono::high_resolution_clock::now();
        auto d_bus_lista = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

        // --- ARRAY ---
        t1 = std::chrono::high_resolution_clock::now();
        for(int x : dados) arr.insert(x);
        t2 = std::chrono::high_resolution_clock::now();
        auto d_ins_arr = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

        t1 = std::chrono::high_resolution_clock::now();
        for(int i=0; i<1000; i++) arr.search(rng() % n);
        t2 = std::chrono::high_resolution_clock::now();
        auto d_bus_arr = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

        // --- AVL ---
        t1 = std::chrono::high_resolution_clock::now();
        for(int x : dados) avl.insert(x);
        t2 = std::chrono::high_resolution_clock::now();
        auto d_ins_avl = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

        t1 = std::chrono::high_resolution_clock::now();
        for(int i=0; i<1000; i++) avl.search(rng() % n);
        t2 = std::chrono::high_resolution_clock::now();
        auto d_bus_avl = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

        std::cout << n << " | Lista | " << d_ins_lista << " | " << d_bus_lista << std::endl;
        std::cout << n << " | Array | " << d_ins_arr << " | " << d_bus_arr << std::endl;
        std::cout << n << " | AVL   | " << d_ins_avl << " | " << d_bus_avl << std::endl;
    }


    return 0;
}