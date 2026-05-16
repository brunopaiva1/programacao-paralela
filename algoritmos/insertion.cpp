#include <iostream>
#include <vector>

int insertion_sort(std::vector<int>& a){
    int key;
    int n = a.size();

    for(int i = 1; i < n; i++){
        key = a[i];
        int j = i - 1;

        while(j >= 0 && j > key){
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }

    return;
}

int main() {
    int n = 32;
    std::vector<int> base_vec(n);

    insertion_sort(base_vec);

return 0;

}