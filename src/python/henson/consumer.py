from netCDF4 import Dataset
import time
import sys

print("consumer before file open")

rootgrp = Dataset("output.nc")

print(rootgrp.variables["v1"][:])

rootgrp.close()
print("consumer completed successfully")
