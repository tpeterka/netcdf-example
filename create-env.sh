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

spack add lowfive
spack add wilkins
spack add henson+python+mpi-wrappers
spack add netcdf-c@4.9+mpi build_system=cmake

# install everything in environment
echo "installing dependencies in environment"
spack install

spack env deactivate

