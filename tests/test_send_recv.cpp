#include "src.hpp"
#include <mpi.h>
#include <unistd.h>   // for sleep
#include <cstdio>
#include <cmath>

int main(int argc, char* argv[])
{
    PMPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // --- First call ---
    double val1 = send_recv_random();

    // Check consistency across ranks using allreduce with MPI_MIN
    double min_val1 = 0.0;
    PMPI_Allreduce(&val1, &min_val1, 1, MPI_DOUBLE, MPI_MIN, MPI_COMM_WORLD);


    if (val1 != min_val1) {
        fprintf(stderr, "Rank %d, send_recv_random returned %e but other ranks returned %e\n", rank, val1, min_val1);
        PMPI_Abort(MPI_COMM_WORLD, -1);
    }

    // --- Second call after sleep ---
    sleep(1);
    double val2 = send_recv_random();

    // Make sure numbers differ between first and second call
    if (fabs(val1 - val2) < 1e-12) {
        fprintf(stderr, "send_recv_random returned the same value twice\n");
        PMPI_Abort(MPI_COMM_WORLD, -1);
    }

    PMPI_Finalize();
    return 0;
}
