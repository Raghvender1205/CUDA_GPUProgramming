import pyopencl as cl
import pyopencl.characterize.performance as perf

def main():
    ctx = cl.create_some_context()

    prof_overhead, latency = perf.get_profiling_overhead(ctx)
    print("Command Latency: %gs" % latency)
    print("Profiling Overhead: {:g}s -> {:.1f}%".format(prof_overhead, 100 * prof_overhead / latency))

    queue = cl.CommandQueue(ctx, properties=cl.command_queue_properties.PROFILING_ENABLE)

    print("Empty Kernel: %gs" % perf.get_empty_kernel_time(queue))
    print("Float32 add: %gs GOps/s" % (perf.get_add_rate(queue) / 1e-9))

    for tx_type in [
        perf.HostToDeviceTransfer,
        perf.DeviceToHostTransfer,
        perf.DeviceToDeviceTransfer]:

        print("--------------------------------")
        print(tx_type.__name__)
        print("--------------------------------")

        print("Latency: %g s" % perf.transfer_latency(queue, tx_type))
        for i in range(6, 31, 2):
            bs = 1 << i
            try:
                result = "%g GB/s" % (perf.transfer_bandwidth(queue, tx_type, bs) / 1e-9)
            except Exception as e:
                result = "Exception: %s" % e.__class__.__name__
            print("Bandwidth @ %d bytes: %s" % (bs, result))

if __name__ == '__main__':
    main()