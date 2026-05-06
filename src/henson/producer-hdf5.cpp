#include <diy/mpi/communicator.hpp>
#include <diy/master.hpp>

#include "prod-con.hpp"

#include <hdf5.h>

#define MAX_DIMS 10

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

    int                     elements_per_pe;
    std::vector<size_t>     dim_len(MAX_DIMS);

    // debug
    fmt::print(stderr, "producer: local comm rank {} size {}\n", local_.rank(), local_.size());

    // set up file access property list
    hid_t plist = H5Pcreate(H5P_FILE_ACCESS);
    H5Pset_fapl_mpio(plist, local, MPI_INFO_NULL);

    if (!getenv("HDF5_VOL_CONNECTOR"))
    {
        fmt::print(stderr, "Error: HDF5_VOL_CONNECTOR is not set\n");
        abort();
    } else
        fmt::print(stderr, "HDF5_VOL_CONNECTOR is set\n");

    // create a new file and group using default properties
    hid_t file = H5Fcreate("outfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, plist);

    // decomposition
    std::vector<size_t> starts(1), counts(1);
    dim_len[0]      = 128;
    elements_per_pe = dim_len[0] / local_.size();
    starts[0]       = local_.rank() * elements_per_pe;
    counts[0]       = elements_per_pe;

    // generate dataset v1
    std::vector<int> v1(elements_per_pe);
    for (int i = 0; i < elements_per_pe; i++)
        v1[i] = local_.rank() * elements_per_pe + i;

    // filespace is local subset of global domain
    hid_t filespace = H5Screate_simple (1, &dim_len[0], NULL);
    H5Sselect_hyperslab(filespace, H5S_SELECT_SET, &starts[0], NULL, &counts[0], NULL);

    // memspace is simple counts
    hid_t memspace = H5Screate_simple (1, &counts[0], NULL);

    // write dataset v1
    hid_t dset = H5Dcreate2(file, "v1", H5T_NATIVE_INT, filespace, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    H5Dwrite(dset, H5T_NATIVE_INT, memspace, filespace, H5P_DEFAULT, &v1[0]);

    // debug: print v1
//     for (auto i = 0; i < v1.size(); i++)
//         fmt::print(stderr, "v1[{}] = {}\n", local_.rank() * elements_per_pe + i, v1[i]);

    // clean up
    H5Dclose(dset);
    H5Sclose(memspace);
    H5Sclose(filespace);
    H5Fclose(file);
    H5Pclose(plist);

    // debug
    fmt::print(stderr, "*** producer after closing file ***\n");
}
