#include "src.hpp"

int test_main(int argc, char* argv[])
{
    main(argc, argv);

    if (mpi_finalized == false)
    {
        fprintf(stderr, "MPI was not finalized appropriately.  Make sure to call MPI_Finalize.\n");
        return -1;
    }
    return 0;
}
