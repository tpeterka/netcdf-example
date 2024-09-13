#include <diy/mpi/communicator.hpp>
#include <diy/master.hpp>

#include "prod-con.hpp"

#include <netcdf.h>
#include <netcdf_par.h>

#define MAX_DIMS 10

#define ERR {if(err!=NC_NOERR)printf("Error at line=%d: %s\n", __LINE__, nc_strerror(err));}

herr_t fail_on_hdf5_error(hid_t stack_id, void*)
{
    H5Eprint(stack_id, stderr);
    fprintf(stderr, "An HDF5 error was detected. Terminating.\n");
    exit(1);
}

int main(int argc, char** argv)
{
    diy::mpi::environment   env(argc, argv, MPI_THREAD_MULTIPLE);

    // for some reason, local has to be a duplicate of world, not world itself
    diy::mpi::communicator      world;
    communicator                local;
    MPI_Comm_dup(world, &local);
    diy::mpi::communicator local_(local);

    // enable netCDF logging
    int level = 5;      // 1: min, 5: max
    nc_set_log_level(level);

    int                     ncid;
    int                     elements_per_pe;
    int                     ndims;
    int                     varid1          = -1;
    int                     varid2          = -1;
    std::vector<size_t>     dim_len(MAX_DIMS);
    std::vector<int>        dimid_v1(MAX_DIMS);
    int                     err;

    // debug
    fmt::print(stderr, "producer: local comm rank {} size {}\n", local_.rank(), local_.size());

    // set HDF5 error handler
    H5Eset_auto(H5E_DEFAULT, fail_on_hdf5_error, NULL);

    // create file
    err = nc_create_par("output.nc", NC_NETCDF4 | NC_CLOBBER, local, MPI_INFO_NULL,  &ncid); ERR

    // variable sizes
    int ntime_steps = 3;
    dim_len[0]  = 128;
    dim_len[1]  = 256;

    // define variables

    // ----- variable v1 -----
    err = nc_def_dim(ncid, "s", dim_len[0], &dimid_v1[0]); ERR
    err = nc_def_var(ncid, "v1", NC_INT, 1, &dimid_v1[0], &varid1); ERR
//     fmt::print(stderr, "producer varid1 = {} dimid_v1 = [{}]\n", varid1, dimid_v1[0]);

    // end define mode
    err = nc_enddef(ncid); ERR

    // write variables

    //  ------ variable v1 -----

    // decomposition
    elements_per_pe = dim_len[0] / local_.size();
    std::vector<int> v1(elements_per_pe);
    std::vector<size_t> starts(1), counts(1);
    starts[0] = local_.rank() * elements_per_pe;
    counts[0] = elements_per_pe;
    for (int i = 0; i < elements_per_pe; i++)
        v1[i] = local_.rank() * elements_per_pe + i;

    // set collective access
    err = nc_var_par_access(ncid, varid1, NC_COLLECTIVE); ERR

    // write variable
    err = nc_put_vara_int(ncid, varid1, &starts[0], &counts[0], &v1[0]); ERR

    // ---------------------------

    // close file
    err = nc_close(ncid); ERR

    // debug
    fmt::print(stderr, "*** producer after closing file ***\n");
}
