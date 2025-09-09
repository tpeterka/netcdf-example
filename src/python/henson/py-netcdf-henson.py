#!/usr/bin/env python3

from mpi4py import MPI
import pyhenson as h
import lowfive
import os
import importlib
import time

world = MPI.COMM_WORLD.Dup()
size = world.Get_size()

passthru = True
consumer_procs = int(size / 2)

pm = h.ProcMap(world, [("producer", size - consumer_procs), ("consumer", consumer_procs)])
nm = h.NameMap()

if pm.group() == "producer":
    tag = 0
    lowfive.create_logger("trace")
#     vol = lowfive.create_DistMetadataVOL(pm.local(), pm.intercomm("consumer", tag))
    vol = lowfive.create_VOLBase()
#     vol = lowfive.create_MetadataVOL()

# uncomment the next 4 lines for the MetadataVOL plugin, leave commented for VOLBase
#     if passthru:
#         vol.set_passthru("*", "*")
#     else:
#         vol.set_memory("*", "*")

# uncomment the next line for DistMetadataVOL plugin, leave commented for VOLBase and MetadataVOL
#     vol.set_intercomm("*", "*", 0)

    importlib.import_module("producer")

#     vol.clear_files()

    if passthru:
        print("producer before barrier")
        h.to_mpi4py(pm.intercomm("consumer", tag)).barrier()
        print("producer after barrier")

    # confirm that with a sleep, the problem of closing the producer file too late exists as it does in wilkins
    time.sleep(5)

else:
    tag = 0
#     lowfive.create_logger("debug")
#     vol = lowfive.create_DistMetadataVOL(pm.local(), pm.intercomm("producer", tag))
    vol = lowfive.create_VOLBase()

# uncomment the next 4 lines for the MetadataVOL plugin, leave commented for VOLBase
#     vol = lowfive.create_MetadataVOL()
#     if passthru:
#         vol.set_passthru("*", "*")
#     else:
#         vol.set_memory("*", "*")

# uncomment the next line for DistMetadataVOL plugin, leave commented for VOLBase and MetadataVOL
#     vol.set_intercomm("*", "*", 0)

    if passthru:
        h.to_mpi4py(pm.intercomm("producer", tag)).barrier()

    importlib.import_module("consumer")
