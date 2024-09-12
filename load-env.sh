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
export DIY_PATH=`spack location -i diy`
export FMT_PATH=`spack location -i fmt`

echo "setting flags for running netcdf-example"
export LD_LIBRARY_PATH=$NETCDF_PATH/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$LOWFIVE_PATH/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$HENSON_PATH/lib:$LD_LIBRARY_PATH

# enable VOL plugin
unset HDF5_PLUGIN_PATH
unset HDF5_VOL_CONNECTOR
lowfive_module=`python3 -c "import lowfive; print(lowfive._lowfive.__file__)"`
lowfive_library=`ldd $lowfive_module | awk 'NF == 4 {print $3}; NF == 2 {print $1}' | grep lowfive`
export HDF5_PLUGIN_PATH=`dirname $lowfive_library`
export HDF5_VOL_CONNECTOR="lowfive under_vol=0;under_info={};"
echo "environment variables are set for running LowFive"


