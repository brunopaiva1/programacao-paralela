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

    cout << scenario_name << "\n";
    cout << setw(8) << "Worker" << " | " << setw(8) << "Workload\n";
    for (int w = 0; w < workers; w++) {
        cout << setw(8) << w << " | " << setw(8) << workload[w] << "\n";
    }
    cout << "-> Gargalo: " << makespan << "\n\n";
}

int main() {
    int n = 64;
    int workers = 4;
    vector<int> tasks(n);

    iota(tasks.begin(), tasks.end(), 1);
    int total_work = accumulate(tasks.begin(), tasks.end(), 0);
    
    cout << "Trabalho Total: " << total_work << "\n";
    cout << "Carga Ideal: " << total_work / workers << "\n\n";

    distribute_and_print(tasks, workers, "Sequencial");

    random_device rd;
    mt19937 g(rd());
    
    for (int i = 1; i <= 4; i++) {
        shuffle(tasks.begin(), tasks.end(), g);
        distribute_and_print(tasks, workers, "Aleatoria " + to_string(i));
    }

    return 0;
}