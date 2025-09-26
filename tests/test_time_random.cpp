#include "src.hpp"
#include <vector>
#include "unistd.h"

int main(int argc, char* argv[])
{
    PMPI_Init(&argc, &argv);
    
    int rank, num_procs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    int n = 10;
    int N = num_procs * n;
    std::vector<double> rand_array(N, 0);
    double time0 = time_random_array_generation(N, rand_array.data());
    std::vector<double> rand_array2(N, 0);
    sleep(1);
    double time1 = time_random_array_generation(N, rand_array2.data());
    sleep(1);
    double time2 = time_random_array_generation(N, rand_array2.data());


    int n_same = 0;
    if (time0 == time1)
        n_same++;
    if (time1 == time2)
        n_same++;
    if (n_same == 2)
    {
        fprintf(stderr, "Rank %d is getting the exact same timing every test.  Make sure you are calling MPI_Wtime().\n", rank);
        MPI_Abort(MPI_COMM_WORLD, -1);
    }

    double min_time;
    MPI_Allreduce(&time0, &min_time, 1, MPI_DOUBLE, MPI_MIN, MPI_COMM_WORLD);
    if (time0 != min_time)
    {
        printf("Rank %d, time0 %e, min_time %e\n", rank, time0, min_time);
        fprintf(stderr, "Rank %d is not returning the minimum time across all ranks.  Make sure to call MPI_Allreduce, passing MPI_MIN as the operation.\n", rank);
        MPI_Abort(MPI_COMM_WORLD, -1);
    }

    PMPI_Finalize();
    
    return 0;
}
