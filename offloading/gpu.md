/opt/rocm-6.0.0/llvm/bin/clang++ \
  -fopenmp \
  -fopenmp-targets=amdgcn-amdhsa \
  -Xopenmp-target=amdgcn-amdhsa -march=gfx902 \
  -I/usr/include/c++/11 \
  -I/usr/include/x86_64-linux-gnu/c++/11 \
  -I/usr/lib/gcc/x86_64-linux-gnu/11/include \
  -L/usr/lib/gcc/x86_64-linux-gnu/11 \
  -lstdc++ \
  -o hello_gpu teste_gpu.cpp
