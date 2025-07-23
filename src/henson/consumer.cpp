#include <diy/mpi/communicator.hpp>
#include <diy/master.hpp>
#include <thread>
#include "prod-con.hpp"

#include <netcdf.h>
#include <netcdf_par.h>

#include "fmt/format.h"

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
    std::vector<int>        dim_len(MAX_DIMS);
    std::vector<int>        dimid_v1(MAX_DIMS);
    int                     nvars;                  // number of variables
    int                     ngatts;                 // number of global attributes
    int                     unlimdimid;             // id of unlimited dim
    int                     err;;

    // debug
    fmt::print(stderr, "consumer: local comm rank {} size {}\n", local_.rank(), local_.size());

    // set HDF5 error handler
    H5Eset_auto(H5E_DEFAULT, fail_on_hdf5_error, NULL);

    // open file for reading
    err = nc_open_par("output.nc", NC_NOWRITE, local, MPI_INFO_NULL, &ncid); ERR

    // read the metadata

    // global metadata
    err = nc_inq(ncid, &ndims, &nvars, &ngatts, &unlimdimid); ERR
    fmt::print(stderr, "*** consumer metadata: ndims {} nvars {} ngatts {} unlimdimid {} ***\n",
            ndims, nvars, ngatts, unlimdimid);

    // dimensions
    char dimname[256];
    size_t dimlen;
    for (int d = 0; d < ndims; d++)
    {
        err = nc_inq_dim(ncid, d, dimname, &dimlen); ERR
        dim_len[d] = dimlen;
        fmt::print(stderr, "*** consumer dim {} dim_name {} dimlen {} ***\n", d, dimname, dimlen);
    }

    // variable info
    char varname[256];
    std::vector<int>        dimids(MAX_DIMS);       // dimension ids
    int                     natts;                  // number of variable attributes
    nc_type                 dtype;                  // netCDF data type of this variable
    err = nc_inq_var(ncid, 0, varname, &dtype, &ndims, &dimids[0], &natts); ERR
    fmt::print(stderr, "*** consumer varname {} dtype {} ndims {} natts {}\n", varname, dtype, ndims, natts);

    // read variables

    //  ------ variable v1 -----

    // decomposition
    elements_per_pe = dim_len[0] / local_.size();
    std::vector<int> v1(elements_per_pe);
    std::vector<size_t> starts(1), counts(1);
    starts[0] = local_.rank() * elements_per_pe;
    counts[0] = elements_per_pe;

    // read the metadata (get variable ID)
    nc_inq_varid(ncid, "v1", &varid1);

    // set collective access
    err = nc_var_par_access(ncid, varid1, NC_COLLECTIVE); ERR

    // read variable
    err = nc_get_vara_int(ncid, varid1, &starts[0], &counts[0], &v1[0]); ERR

    // check the data values
    for (int i = 0; i < elements_per_pe; i++)
    {
        if (v1[i] != local_.rank() * elements_per_pe + i)
        {
            fmt::print(stderr, "*** consumer error: v1[{}] = {} which should be {} ***\n", i, v1[i], local_.rank() * elements_per_pe + i);
            abort();
        }
    }

    // ------------------------------

    // close file
    err = nc_close(ncid); ERR

    // debug
    fmt::print(stderr, "*** consumer after closing file ***\n");
}

