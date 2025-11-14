#!/bin/bash

# activate the environment
export SPACKENV=netcdf-example-env
spack env deactivate > /dev/null 2>&1
spack env activate $SPACKENV
echo "activated spack environment $SPACKENV"

echo "setting flags for building netcdf-example"
export NETCDF_PATH=`spack location -i netcdf-c`
export LOWFIVE_PATH=`spack location -i lowfive`
export HENSON_PATH=`spack location -i henson`
# export DIY_PATH=`spack location -i diy`
# export FMT_PATH=`spack location -i fmt`
export WILKINS_PATH=`spack location -i wilkins`
export HENSON=`spack location -i henson`

echo "setting flags for running netcdf-example"
export LD_LIBRARY_PATH=$NETCDF_PATH/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$NETCDF_PATH/lib64:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$LOWFIVE_PATH/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$HENSON_PATH/lib:$LD_LIBRARY_PATH

# enable VOL plugin
unset HDF5_PLUGIN_PATH
unset HDF5_VOL_CONNECTOR
export HDF5_PLUGIN_PATH=$LOWFIVE/lib
export HDF5_VOL_CONNECTOR="lowfive under_vol=0;under_info={};"
echo "environment variables are set for running LowFive"

# ensures that python is the spack-installed one
spack load python

