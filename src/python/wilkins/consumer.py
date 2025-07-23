from netCDF4 import Dataset

rootgrp = Dataset("output.nc", "r", format="NETCDF4")

print("consumer:", rootgrp.data_model)

rootgrp.close()
