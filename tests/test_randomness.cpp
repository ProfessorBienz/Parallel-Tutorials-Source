#include "src.hpp"

int main(int argc, char* argv[])
{
    PMPI_Init(&argc, &argv);
    
    int num_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    double val0, val1;
    val0 = generate_random();
    val1 = generate_random();

    if (val0 == val1)
    {
        fprintf(stderr, "Rank %d is getting the same data each time an array is generated.  Make sure to randomize your seed with time.\n");
        MPI_Abort(MPI_COMM_WORLD, -1);
    }

    PMPI_Finalize();
    
    return 0;
}
