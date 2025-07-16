#include "src.hpp"

mpi_initialized = false;
mpi_finalized = false;
printed = false;
num_procs = 0;

int __wrap_MPI_Init(int* argc, char*** argv)
{
    mpi_initialzied = true;
    int ierr = PMPI_Init(argc, argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
}


int __wrap_MPI_Finalize()
{
    mpi_finalized = true;
    return PMPI_Finalize();
}

