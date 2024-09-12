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
source /path/to/moab-diy/load-env.sh
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

There are three options for running the example: prod-con (with no workflow system), henson (using the henson system), and wilkins (using the wilkins system). Currently only prod-con is implemented.

prod-con

```
cd /path/to/netcdf-example/install/bin/prod-con
mpiexec -n <procs> ./prod-con -m 0 -f 1     # file mode
mpiexec -n <procs> ./prod-con -m 1 -f 0     # memory mode
```

-----
