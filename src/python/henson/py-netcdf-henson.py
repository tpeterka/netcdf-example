#!/usr/bin/env python3

from mpi4py import MPI
import pyhenson as h
import lowfive
from pathlib import Path
import os

import importlib
import runpy

world = MPI.COMM_WORLD.Dup()
size = world.Get_size()

passthru = True
consumer_procs = int(size / 2)

pm = h.ProcMap(world, [("producer", size - consumer_procs), ("consumer", consumer_procs)])
nm = h.NameMap()

if pm.group() == "producer":
    tag = 0
#     lowfive.create_logger("debug")
    vol = lowfive.create_DistMetadataVOL(pm.local(), pm.intercomm("consumer", tag))
    if passthru:
        vol.set_passthru("*", "*")
    else:
        vol.set_memory("*", "*")
    vol.set_intercomm("*", "*", 0)

# this works in passthru but fails in metadata if a file doesn't exist
#     import producer
#     producer.prod()

# this works in passthru but fails in metadata if a file doesn't exist
    producer = importlib.import_module("producer")
    producer.prod()
#     del producer

# this works in passthru but fails in metadata if a file doesn't exist
#     exec(open("producer.py").read())

# this works in passthru only if a file already exists, otherwise fails
# don't recommend using it
#     runpy.run_path(path_name='producer.py')

    if passthru:
        h.to_mpi4py(pm.intercomm("consumer", tag)).barrier()
else:
    tag = 0
#     lowfive.create_logger("info")
    vol = lowfive.create_DistMetadataVOL(pm.local(), pm.intercomm("producer", tag))
    if passthru:
        vol.set_passthru("*", "*")
    else:
        vol.set_memory("*", "*")
    vol.set_intercomm("*", "*", 0)

    if passthru:
        h.to_mpi4py(pm.intercomm("producer", tag)).barrier()

    import consumer
    consumer.cons()
