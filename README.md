# netcdf-example
Workflow example using NetCDF-4

# Instructions for Building and Running

Installation is done through Spack. If you don't have Spack installed or if Spack is new to you, go [here](https://spack.readthedocs.io/en/latest/) first.

-----

## Adding the following Spack repositories to your local Spack installation

LowFive
```
git clone https://github.com/diatomic/LowFive
spack repo add LowFive
```

Wilkins
```
git clone https://github.com/orcunyildiz/wilkins
spack repo add wilkins
```

Optional: FTK
```
git clone https://github.com/hguo/spack-mpas-o
spack repo add spack-mpas-o
```

Optional: FTK
Change ftk Spack recipe to pull from a fork
```
spack edit ftk
```

Edit lines 14-16 as follows
```
homepage = "https://github.com/tpeterka/ftk"
url = "https://github.com/tpeterka/ftk/archive/0.0.7.1.tar.gz"
git = "https://github.com/tpeterka/ftk.git"
```
And save the file.

-----

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

```
source /path/to/netcdf-example/load-env.sh
```

First time: create an output.nc file

Because of a quirk in NetCDF, there needs to be an output file `output.nc` on disk, otherwise the program will complain. For the prod-con example, run file mode first. For the henson and wilkins
examples, edit the script to set pasthru to True for the first run. Alternatively, there is a blank.nc file included in the top level of this repository. You can copy it to the install directory of
and rename it to `output.nc`.

There are four options for running the example: prod-con (with no workflow system, netcdf producer and consumer), henson (using the henson system with netcdf consumer), henson-ftk (using the henson system with ftk consumer), and wilkins (using the wilkins system with netcdf consumer).

### prod-con

```
source /path/to/netcdf-example/load-env.sh
cd /path/to/netcdf-example/install/bin/prod-con
mpiexec -n <procs> ./prod-con -m 0 -f 1     # file mode
mpiexec -n <procs> ./prod-con -m 1 -f 0     # memory mode
```

### henson

```
source /path/to/netcdf-example/load-env.sh
cd /path/to/netcdf-example/install/bin/henson
mpiexec -n <procs> python3 ./netcdf-henson.py
```

Changes to file mode, memory mode, etc. are made in `path/to/netcdf-example/install/bin/henson/netcdf-henson.py`. Alternatively, you may change the version of the same file in the source directory
`/path/to/netcdf-example/src/henson/netcdf-henson.py` and rebuild. The build copies the Python script from the src directory to the install directory. The copy in the install directory is the one that
is executed.

### henson-ftk

Export spack install location of FTK:
```
export FTK=`spack location -i ftk`
```

Running standalone ftk as a test
```
source /path/to/netcdf-example/load-env.sh
unset HDF5_VOL_CONNECTOR
unset HDF5_PLUGIN_PATH
cd /path/to/netcdf-example/install/bin/henson-ftk
./run-ftk.sh
```

Running in a workflow
```
source /path/to/netcdf-example/load-env.sh
cd /path/to/netcdf-example/install/bin/henson-ftk
mpiexec -n <procs> python3 ./henson-ftk.py
```

Changes to file mode, memory mode, etc. are made in `path/to/netcdf-example/install/bin/henson-ftk/henson-ftk.py`. Alternatively, you may change the version of the same file in the source directory
`/path/to/netcdf-example/src/henson-ftk/henson-ftk.py` and rebuild. The build copies the Python script from the src directory to the install directory. The copy in the install directory is the one that
is executed.

### wilkins

```
source /path/to/netcdf-example/load-env.sh
cd /path/to/netcdf-example/install/bin/wilkins
./wilkins-run.sh
```

Changes to file mode, memory mode, etc. are made in `path/to/netcdf-example/install/bin/wilkins/wilkins-config.yaml`. The total number of MPI processes must also agree in
`path/to/netcdf-example/install/bin/wilkins/wilkins-run.sh`. Alternatively, you may make changes in the source directory `/path/to/netcdf-example/src/wilkins` and rebuild. The build process copies the
wilkins configuration and run scripts to the install directory. The version in the install directory is the one that is executed.

### python/henson

```
source /path/to/netcdf-example/load-env.sh
cd /path/to/netcdf-example/install/bin/python/henson
mpiexec -n 2 -l python3 -u ./py-netcdf-henson.py
```

Changes to file mode, memory mode, etc. are made in `path/to/netcdf-example/install/bin/python/henson/py-netcdf-henson.py`. Alternatively, you may change the version of the same file in the source directory
`/path/to/netcdf-example/src/python/henson/py-netcdf-henson.py` and rebuild. The build copies the Python script from the src directory to the install directory. The copy in the install directory is the one that
is executed.

### python/wilkins

```
source /path/to/netcdf-example/load-env.sh
cd /path/to/netcdf-example/install/bin/python/wilkins
./wilkins-run.sh
```

Changes to file mode, memory mode, etc. are made in `path/to/netcdf-example/install/bin/python/wilkins/wilkins-config.yaml`. The total number of MPI processes must also agree in
`path/to/netcdf-example/install/bin/python/wilkins/wilkins-run.sh`. Alternatively, you may make changes in the source directory `/path/to/netcdf-example/src/wilkins` and rebuild. The build process copies the
wilkins configuration and run scripts to the install directory. The version in the install directory is the one that is executed.

-----
