import pyopencl as cl
import pyopencl.array as cl_array
import numpy as np
import numpy.linalg as la

a = np.random.rand(50000).astype(np.float32)
b = np.random.rand(50000).astype(np.float32)

ctx = cl.create_some_context()
queue = cl.CommandQueue(ctx)

a_dev = cl_array.to_device(queue, a)
b_dev = cl_array.to_device(queue, b)
dest_dev = cl_array.empty_like(a_dev)

prg = cl.Program(ctx, """
__kernel void sum(__global const float *a, 
    __global const float *b, __global float *c) {
    int gid = get_global_id(0);
    c[gid] = a[gid] + b[gid]; 
}
""").build()

kernel = prg.sum 
kernel(queue, a.shape, None, a_dev.data, a_dev.data, dest_dev.data)

print(la.norm((dest_dev - (a_dev + b_dev)).get()))