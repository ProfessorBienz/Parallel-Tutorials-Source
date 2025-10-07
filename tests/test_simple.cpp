#include "src.hpp"
#include <mpi.h>
#include <unistd.h>   // for sleep
#include <cstdio>
#include <cmath>
#include <vector>

int main(int argc, char* argv[])
{
    PMPI_Init(&argc, &argv);

    int rank, num_procs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    int N = 10;
    std::vector<double> send_array(N);
    srand(time(NULL) * (rank+1));
    for (int i = 0; i < N; i++)
        send_array[i] = ((double) rand())/RAND_MAX;
    std::vector<double> recv_array(N * num_procs);
    std::vector<double> std_recv_array(N*num_procs);
    MPI_Allgather(send_array.data(), N, MPI_DOUBLE, 
            std_recv_array.data(), N, MPI_DOUBLE, MPI_COMM_WORLD);

    allgather_simple(send_array.data(), recv_array.data(), N);

    for (int i = 0; i < N*num_procs; i++)
    {
        if (std_recv_array[i] != recv_array[i])
        {
            fprintf(stderr, "Rank %d, Position %d, std %e, yours %e\n", rank, i, std_recv_array[i], recv_array[i]);
            MPI_Abort(MPI_COMM_WORLD, -1);
        }
    }

    PMPI_Finalize();
    return 0;

}

