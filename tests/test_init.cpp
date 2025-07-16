#include "src.hpp"

int test_main(int argc, char* argv[])
{
    main(argc, argv);

    if (mpi_initialized == false)
    {
        fprintf(stderr, "MPI was not initialized.  Make sure to call MPI_Init.\n");
        return -1;
    }

    return 0;
}
