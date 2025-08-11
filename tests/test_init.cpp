#include "src.hpp"

int main(int argc, char* argv[])
{
    PMPI_Init(&argc, &argv);
    
    tutorial_main(argc, argv);

    if (mpi_initialized == false)
    {
        fprintf(stderr, "MPI was not initialized.  Make sure to call MPI_Init.\n");
        return -1;
    }

    PMPI_Finalize();
    
    return 0;
}
