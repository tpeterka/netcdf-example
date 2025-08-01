from netCDF4 import Dataset
import sys

def cons():
    print("consumer before file open")

    rootgrp = Dataset("output.nc")

    print(rootgrp.variables["v1"][:])

    rootgrp.close()
    print("consumer completed successfully")
#     sys.exit("consumer exiting")
