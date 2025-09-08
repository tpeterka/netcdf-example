from netCDF4 import Dataset

print("consumer before file open")

rootgrp = Dataset("output.nc")

print(rootgrp.variables["v1"][:])

rootgrp.close()
print("consumer completed successfully")
