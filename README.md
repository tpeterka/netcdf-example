# netcdf-example
Workflow example using NetCDF-4

# Instructions for Building and Running

Installation is done through Spack. If you don't have Spack installed or if Spack is new to you, go [here](https://spack.readthedocs.io/en/latest/) first.

## Setting up Spack environment

### First time: create and load the Spack environment

```
git clone https://github.com/tpeterka/netcdf-example
cd /path/to/netcdf-example
source ./create-env.sh     # requires being in the same directory to work properly
source ./load-env.sh
```

### Subsequent times: load the Spack environment

```
source /path/to/netcdf-example/load-env.sh
```

----

## Building netcdf-example

```
cd build
rm CMakeCache.txt
cmake .. \
-DCMAKE_INSTALL_PREFIX=/path/to/netcdf-example/install
make -j install
```

-----

## Running netcdf-example

First time: create an output.nc file

Because of a quirk in NetCDF, there needs to be an output file `output.nc` on disk, otherwise the program will complain. For the prod-con example, run file mode first. For the henson and wilkins
examples, edit the script to set pasthru to True for the first run. Alternatively, there is a blank.nc file included in the top level of this repository. You can copy it to the install directory of
and rename it to `output.nc`.

There are three options for running the example: prod-con (with no workflow system), henson (using the henson system), and wilkins (using the wilkins system).

prod-con

```
cd /path/to/netcdf-example/install/bin/prod-con
mpiexec -n <procs> ./prod-con -m 0 -f 1     # file mode
mpiexec -n <procs> ./prod-con -m 1 -f 0     # memory mode
```

henson

```
cd /path/to/netcdf-example/install/bin/henson
mpiexec -n <procs> python3 ./netcdf-henson.py
```

Changes to file mode, memory mode, etc. are made in `path/to/netcdf-example/install/bin/henson/netcdf-henson.py`. Alternatively, you may change the version of the same file in the source directory
`/path/to/netcdf-example/src/henson/netcdf-henson.py` and rebuild. The build copies the Python script from the src directory to the install directory. The copy in the install directory is the one that
is executed.

-----
