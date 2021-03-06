# Elementwise Kernel Operation in PyCUDA
import pycuda.gpuarray as gpuarray
import pycuda.autoinit

import numpy as np
import numpy.linalg as la

from pycuda.curandom import rand as curand
from pycuda.elementwise import ElementwiseKernel


a_gpu = curand((50,))
b_gpu = curand((50,))

lin_comb = ElementwiseKernel(
        "float a, float *x, float b, float *y, float *z",
        "z[i] = my_f(a*x[i], b*y[i])",
        "linear_combination",
        preamble="""
        __device__ float my_f(float x, float y)
        { 
          return sin(x*y);
        }
        """)

c_gpu = gpuarray.empty_like(a_gpu)
lin_comb(5, a_gpu, 6, b_gpu, c_gpu)

assert la.norm(c_gpu.get() - np.sin((5*a_gpu*6*b_gpu).get())) < 1e-5

print(c_gpu)