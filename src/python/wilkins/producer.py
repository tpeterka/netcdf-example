from netCDF4 import Dataset
import numpy as np

# root group
rootgrp = Dataset("output.nc", "w", format="NETCDF4")

# dimension
s = rootgrp.createDimension("s", 128)

# variable
v1 = rootgrp.createVariable("v1","i4",("s",))
v = np.arange(0,128)
v1[:] = v

rootgrp.close()
