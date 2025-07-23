#!/bin/bash

export SPACKENV=netcdf-example-env
export YAML=$PWD/env.yaml

# create spack environment
echo "creating spack environment $SPACKENV"
spack env deactivate > /dev/null 2>&1
spack env remove -y $SPACKENV > /dev/null 2>&1
spack env create $SPACKENV $YAML

# activate environment
echo "activating spack environment"
spack env activate $SPACKENV

spack add mpich@4
spack add hdf5@1.14+hl+mpi
spack add lowfive
spack add wilkins
spack add henson+python+mpi-wrappers
spack add netcdf-c@4.9+mpi build_system=cmake
spack add parallel-netcdf
spack add netcdf-fortran@4.5.3
spack add py-netcdf4
spack add diy@master
spack add fmt

# the following is for optional ftk consumer w/ CUDA for GPU; comment out if not needed
# spack add cuda
# spack add vtk@9.2.2
# spack add ndarray+hdf5+netcdf+mpi+cuda+vtk
# spack develop ftk@mpas+cuda ^ndarray+hdf5+netcdf+mpi+cuda+vtk
# spack add ftk@mpas+cuda ^ndarray+hdf5+netcdf+mpi+cuda+vtk

# the following is for optional ftk consumer w/o CUDA for CPU; comment out if not needed
# spack add vtk@9.2.2
# spack add ndarray+hdf5+netcdf+mpi+vtk
# # spack develop ftk@mpas+cuda ^ndarray+hdf5+netcdf+mpi+vtk
# spack add ftk@mpas+cuda ^ndarray+hdf5+netcdf+mpi+vtk

# install everything in environment
echo "installing dependencies in environment"
spack install henson        # install henson so that henson path is set
export HENSON=`spack location -i henson`
spack install

spack env deactivate

