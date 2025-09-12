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

    std::vector<double> rand_array2(n);
    generate_random_array(N, rand_array.data());

    int n_same = 0;
    for (int i = 0; i < n; i++)
       if (rand_array[i] == rand_array2[i])
          n_same++;
    if (n_same == n) 
    {
        fprintf(stderr, "Rank %d is getting the same data each time an array is generated.  Make sure to randomize your seed with time.\n");
        MPI_Abort(MPI_COMM_WORLD, -1);
    }

    PMPI_Finalize();
    
    return 0;
}
