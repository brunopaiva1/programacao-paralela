#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <omp.h>

void merge(std::vector<int> &A, std::vector<int> &B, long long begin, long long middle, long long end) {
  long long i = begin;
  long long j = middle + 1;
  long long k = begin;

  while (i <= middle && j <= end) {
    if (A[i] <= A[j]) {
      B[k++] = A[i++];
    } else {
      B[k++] = A[j++];
    }
  }

  while (i <= middle) {
    B[k++] = A[i++];
  }
  
  while (j <= end) {
    B[k++] = A[j++];
  }

  for (long long idx = begin; idx <= end; idx++) {
    A[idx] = B[idx];
  }
}

void parallel_merge_sort(std::vector<int> &A, std::vector<int> &B, long long begin, long long end, int depth = 0) {
  if (begin < end) {
    if (end - begin < 8192) {
      std::sort(A.begin() + begin, A.begin() + end + 1);
      return;
    }

    long long middle = begin + (end - begin) / 2;

    if (depth < 5) {
#pragma omp task shared(A, B)
      parallel_merge_sort(A, B, begin, middle, depth + 1);

#pragma omp task shared(A, B)
      parallel_merge_sort(A, B, middle + 1, end, depth + 1);

#pragma omp taskwait
    } else {
      parallel_merge_sort(A, B, begin, middle, depth + 1);
      parallel_merge_sort(A, B, middle + 1, end, depth + 1);
    }

    merge(A, B, begin, middle, end);
  }
}

int main(int argc, char *argv[]) {
  if (argc < 3) return 1;

  long long n = std::atoll(argv[1]);
  int threads = std::atoi(argv[2]);

  std::vector<int> A(n);
  std::vector<int> B(n); 

  for (auto &v : A) {
    v = rand();
  }

  omp_set_num_threads(threads);

  double start = omp_get_wtime();

#pragma omp parallel
  {
#pragma omp single
    parallel_merge_sort(A, B, 0, n - 1);
  }
  
  double end = omp_get_wtime();

  std::cout << n << "," << threads << "," << (end - start) << "\n";

  return 0;
}