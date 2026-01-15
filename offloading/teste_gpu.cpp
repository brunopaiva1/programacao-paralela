#include <iostream>
#include <cstdio>
#include <omp.h>

int main() {
  int did_offload = 0;

  #pragma omp target map(tofrom: did_offload)
  {
    // Evitar usar std::cout aqui!
    // Use printf se quiser ver algo no device (depuração).
    printf("[on device] hello\\n");
    did_offload = 1;
  }

  if (!did_offload) {
    std::cout << "[Rodou no HOST (CPU)] - Falha no Offload!\n";
  } else {
    std::cout << "[Rodou no DEVICE (GPU)]\n";
  }
  return 0;
}
