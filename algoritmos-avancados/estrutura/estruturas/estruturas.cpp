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
class sortedArray {
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

            curr = curr->next
        }
        return false;
    }
};



int main(){
    return 0;
}