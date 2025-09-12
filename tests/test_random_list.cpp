#include "src.hpp"

int main(int argc, char* argv[])
{
    PMPI_Init(&argc, &argv);
    
    int num_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    int n = 10;
    int N = num_procs * n;
    std::vector<double> rand_array(N, 0);
    generate_random_array(N, rand_array.data());
    for (int i = n; i < N; i++)
        if (rand_array[i] != 0)
        {
            fprintf(stderr, "Rank %d generated too many numbers.  N is %d, so each rank should be generating a list of %d numbers\n", rank, N, n);
            MPI_Abort(MPI_COMM_WORLD, -1);
        }

    PMPI_Finalize();
    
    return 0;
}
