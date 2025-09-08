#!/usr/bin/env python3

from mpi4py import MPI
import pyhenson as h
import lowfive
from pathlib import Path
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
    lowfive.create_logger("debug")
    vol = lowfive.create_DistMetadataVOL(pm.local(), pm.intercomm("consumer", tag))
    if passthru:
        vol.set_passthru("*", "*")
    else:
        vol.set_memory("*", "*")
    vol.set_intercomm("*", "*", 0)

    # set the following path to point to your installation of producer
    prod = h.Puppet("./cpp-producer-henson.so", [], pm, nm)

    prod.proceed()

    if passthru:
        h.to_mpi4py(pm.intercomm("consumer", tag)).barrier()

    time.sleep(5)

else:
    tag = 0
#     lowfive.create_logger("debug")
    vol = lowfive.create_DistMetadataVOL(pm.local(), pm.intercomm("producer", tag))
    if passthru:
        vol.set_passthru("*", "*")
    else:
        vol.set_memory("*", "*")
    vol.set_intercomm("*", "*", 0)

    if passthru:
        h.to_mpi4py(pm.intercomm("producer", tag)).barrier()

    importlib.import_module("consumer")
