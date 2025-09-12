#include "src.hpp"

int main(int argc, char* argv[])
{
    PMPI_Init(&argc, &argv);
    
    int num_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    double val;
    std::vector<double> proc_vals(num_procs);
    val = generate_random();

    MPI_Allgather(&val, 1, MPI_DOUBLE, proc_vals.data(), 1, MPI_DOUBLE, MPI_COMM_WORLD);
    
    for (int proc = 0; proc < num_procs; proc++)
    {
        if (proc == rank)
            continue;

        if (proc_vals[proc] == val)
            fprintf(stderr, "Ranks %d and %d have same values!  Your random seed is incorrect.\n", rank, proc);
            MPI_Abort(MPI_COMM_WORLD, -1);
        }
    }

    PMPI_Finalize();
    
    return 0;
}
