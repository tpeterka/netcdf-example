from mpi4py import MPI
import numpy as np
from netCDF4 import Dataset

world = MPI.COMM_WORLD
rank = world.Get_rank()
size = world.Get_size()
print("rank", rank, "size", size)

# ----- producer -----

if rank < size / 2:
    print("producer before file create")

    # root group
    rootgrp = Dataset("output.nc", "w", format="NETCDF4")

    # dimension
    s = rootgrp.createDimension("s", 128)

    # variable
    v1 = rootgrp.createVariable("v1","i4",("s",))
    v = np.arange(0,128)
    v1[:] = v

    # clean up and shut down
    rootgrp.sync()
    rootgrp.close()
    print("producer completed successfully")

    # synchronize with consumer
    world.Barrier()

# ----- consumer -----

else:
    print("consumer before file open")

    #synchronize with producer
    world.Barrier()

    # open file
    rootgrp = Dataset("output.nc")

    # print data
    print(rootgrp.variables["v1"][:])

    # clean up and shut down
    rootgrp.close()
    print("consumer completed successfully")
