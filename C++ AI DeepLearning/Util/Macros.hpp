#ifndef MACROS_HPP
#define MACROS_HPP

#define CUDA_BACKEND

/// Compile the source code with NVCC to use CUDA.
#ifdef __NVCC__
#define CUDA_BACKEND
#endif

#define CUDA_MAX_THREADS 1024
#define CUDA_MAX_CORES 65535

#endif // MACROS_HPP
