#include "src.hpp"
#include <vector>

int main(int argc, char* argv[])
{
    PMPI_Init(&argc, &argv);
    
    int rank, num_procs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    double val;
    std::vector<double> proc_vals(num_procs, 0);
    val = generate_random();
    printf("Rank %d, val %e\n", rank, val);

    MPI_Allgather(&val, 1, MPI_DOUBLE, proc_vals.data(), 1, MPI_DOUBLE, MPI_COMM_WORLD);
    
    for (int proc = 0; proc < num_procs; proc++)
    {
        if (proc != rank && proc_vals[proc] == val)
        {
            fprintf(stderr, "Ranks %d and %d have same values (%e, %e)!  Your random seed is incorrect.\n", rank, proc, val, proc_vals[proc]);
            MPI_Abort(MPI_COMM_WORLD, -1);
        }
    }

    PMPI_Finalize();
    
    return 0;
}
