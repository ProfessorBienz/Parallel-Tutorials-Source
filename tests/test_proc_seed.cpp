#include "src.hpp"

int main(int argc, char* argv[])
{
    PMPI_Init(&argc, &argv);
    
    int num_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    int n = 10;
    int N = num_procs * n;
    std::vector<double> rand_array(n);
    generate_random_array(N, rand_array.data());

    std::vector<double> gathered_array(N);
    MPI_Allgather(rand_array.data(), n, MPI_DOUBLE, gathered_array.data(), n, MPI_DOUBLE, MPI_COMM_WORLD);
    
    for (int proc = 0; proc < num_procs; proc++)
    {
        int n_same = 0;

        if (proc == rank)
            continue;

        for (int i = 0; i < n; i++)
        {
            if (rand_array[i] == gathered_array[proc*n + i])
                n_same++;
        }
        if (n_same == n)
        {
            fprintf(stderr, "Ranks %d and %d have same values!  Your random seed is incorrect.\n", rank, proc);
            MPI_Abort(MPI_COMM_WORLD, -1);
        }
    }

    PMPI_Finalize();
    
    return 0;
}
