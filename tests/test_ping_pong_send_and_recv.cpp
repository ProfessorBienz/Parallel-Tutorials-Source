#include "src.hpp"
#include <mpi.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>

int main(int argc, char* argv[])
{
    PMPI_Init(&argc, &argv);

    int rank;
    PMPI_Comm_rank(MPI_COMM_WORLD, &rank);

    const int N = 100;
    double send_array[N];
    double recv_array[N];

    // Fill send_array with distinct values depending on rank
    for (int i = 0; i < N; i++) {
        send_array[i] = rank * 1000.0 + i;
    }

    ping_pong_send_and_recv(N, send_array, recv_array);

    // Check correctness:
    // Rank 0’s recv_array should equal Rank 1’s send_array
    // Rank 1’s recv_array should equal Rank 0’s send_array
    bool ok = true;
    for (int i = 0; i < N; i++) {
        double expected = (1 - rank) * 1000.0 + i;
        if (fabs(recv_array[i] - expected) > 1e-12) {
            fprintf(stderr, "ping_pong_send_and_recv failed at rank %d, index %d: got %f expected %f\n",
                    rank, i, recv_array[i], expected);
            ok = false;
            break;
        }
    }

    if (!ok) {
        PMPI_Abort(MPI_COMM_WORLD, -1);
    }

    PMPI_Finalize();
    return 0;
}
