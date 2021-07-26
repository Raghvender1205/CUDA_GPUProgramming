import pycuda.autoinit
import pycuda.gpuarray as gpuarray
import pycuda.driver as cuda
import numpy as np

free_bytes, total_bytes = cuda.mem_get_info()
exp = 10
print(free_bytes)
print(total_bytes)

while True:
    fill_floats = free_bytes // 4 
    if fill_floats < 0:
        raise RuntimeError("Could'nt find allocatable size")
    try:
        print('alloc', fill_floats)
        ary = gpuarray.empty((fill_floats,), dtype=np.float32)
        break
    except:
        pass

    exp += 1

ary.fill(float("nan"))

print("Filled %d out of %d bytes with NaNs" % (fill_floats * 4, free_bytes))
