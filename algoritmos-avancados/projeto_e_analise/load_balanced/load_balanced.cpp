#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include <iomanip>

using namespace std;

void distribute_and_print(const vector<int>& tasks, int workers, const string& scenario_name) {
    int n = tasks.size();
    int chunksize = n / workers;
    vector<int> workload(workers, 0);
    int makespan = 0;

    for (int w = 0; w < workers; w++) {
        for (int i = w * chunksize; i < (w + 1) * chunksize; i++) {
            workload[w] += tasks[i];
        }
        makespan = max(makespan, workload[w]);
    }

    cout << setw(8) << "Worker" << " | " << setw(8) << "Workload\n";
    for (int w = 0; w < workers; w++) {
        cout << setw(8) << w << " | " << setw(8) << workload[w] << "\n";
    }
    cout << "-> Gargalo (Makespan): " << makespan << "\n\n";
}

int main() {
    int n = 64;
    int workers = 4;
    vector<int> tasks(n);

    iota(tasks.begin(), tasks.end(), 1);
    int total_work = accumulate(tasks.begin(), tasks.end(), 0);
    
    cout << "Trabalho Total: " << total_work << "\n";
    cout << "Carga Ideal por Trabalhador: " << total_work / workers << "\n";

    distribute_and_print(tasks, workers, "Distribuição Sequencial (Pior Caso)");

    mt19937 g(42);
    shuffle(tasks.begin(), tasks.end(), g);
    
    distribute_and_print(tasks, workers, "Distribuição com Permutação Aleatória");

    return 0;
}