import pycuda.driver as driver

driver.init()
print("%d Device(s) found." % driver.Device.count())

for ordinal in range(driver.Device.count()):
    dev = driver.Device(ordinal)
    print("Device #%d: %s" % (ordinal, dev.name()))
    print("  Compute Capability: %d.%d" % dev.compute_capability())
    print("  Total Memory: %s KB" % (dev.total_memory()//(1024)))
    atts = [(str(att), value)
            for att, value in list(dev.get_attributes().items())]
    atts.sort()

    for att, value in atts:
        print(f"  {att}: {value}")
