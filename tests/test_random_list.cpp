#include "src.hpp"
#include <vector>

int main(int argc, char* argv[])
{
    PMPI_Init(&argc, &argv);
    
    int rank, num_procs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    int n = 10;
    int N = num_procs * n;
    std::vector<double> rand_array(N, 0);
    generate_random_array(N, rand_array.data());
    std::vector<double> rand_array2(N, 0);
    generate_random_array(N, rand_array2.data());

    int n_same = 0;
    for (int i = 0; i < n; i++)
        if (rand_array[i] == rand_array2[i])
            n_same++;
    if (n_same == n)
    {
        fprintf(stderr, "Rank %d's array is not random.  Make sure your seed is based on time.\n", rank);
        MPI_Abort(MPI_COMM_WORLD, -1);
    }

    std::vector<double> gathered_array(N, 0);
    MPI_Allgather(rand_array.data(), n, MPI_DOUBLE, gathered_array.data(),
            n, MPI_DOUBLE, MPI_COMM_WORLD);
    n_same = 0;
    for (int proc = 0; proc < num_procs; proc++)
    {
        if (rank == proc)
            continue;
        n_same = 0;
        for (int i = 0; i < n; i++)
            if (rand_array[i] == gathered_array[proc*n+i])
                n_same++;
        if (n_same == n)
        {
            fprintf(stderr, "Ranks %d and %d generated same arrays.  Make sure to seed based on rank\n", rank);
            MPI_Abort(MPI_COMM_WORLD, -1);
        }
    }


    for (int i = n; i < N; i++)
        if (rand_array[i] != 0)
        {
            fprintf(stderr, "Rank %d generated too many numbers.  N is %d, so each rank should be generating a list of %d numbers\n", rank, N, n);
            MPI_Abort(MPI_COMM_WORLD, -1);
        }

    PMPI_Finalize();
    
    return 0;
}
