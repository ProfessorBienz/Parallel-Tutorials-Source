#include "src.hpp"
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <vector>


int main(int argc, char* argv[])
{
    PMPI_Init(&argc, &argv);

    int rank, num_procs;
    PMPI_Comm_rank(MPI_COMM_WORLD, &rank);
    PMPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    // Redirect stdout to hello_world.tmp file
    char filename[100];
    snprintf(filename, sizeof(filename), "tmp_%d.txt", rank);
    
    int orig_stdout = dup(fileno(stdout));
    FILE* file = freopen(filename, "w", stdout);

    // Run tutorial with redirected stdout
    tutorial_main(argc, argv);

    // Flush stdout
    fflush(stdout);

    // Restore original stdout
    dup2(orig_stdout, fileno(stdout));

    // Close open file descriptors
    close(orig_stdout);
    fclose(file);

    file = fopen(filename, "r");

    // Get file size
    std::vector<int> counts(7, 0);
    int c;
    while ((c = getc(file)) != EOF) {
        if (c == 'h' || c == 'H')
            counts[0]++;
        else if (c == 'e' || c == 'E')
            counts[1]++;
        else if (c == 'l' || c == 'L')
            counts[2]++;
        else if (c == 'o' || c == 'O')
            counts[3]++;
        else if (c == 'w' || c == 'W')
            counts[4]++;
        else if (c == 'r' || c == 'R')
            counts[5]++;
        else if (c == 'd' || c == 'D')
            counts[6]++;
    }

    if (counts[0] < 1)
    {
        fprintf(stderr, "Rank %d did not print 1 H. Counts %d\n", rank, counts[0]);
        MPI_Abort(MPI_COMM_WORLD, -1);
    }
    else if (counts[1] < 1)
    {
        fprintf(stderr, "Rank %d did not print 1 e.\n", rank);
        MPI_Abort(MPI_COMM_WORLD, -1);
    }
    else if (counts[2] < 3)
    {
        fprintf(stderr, "Rank %d did not print 3 l's.\n", rank);
        MPI_Abort(MPI_COMM_WORLD, -1);
    }
    else if (counts[3] < 2)
    {
        fprintf(stderr, "Rank %d did not print 2 w's.\n", rank);
        MPI_Abort(MPI_COMM_WORLD, -1);
    }
    else if (counts[4] < 1)
    {
        fprintf(stderr, "Rank %d did not print 1 r.\n", rank);
        MPI_Abort(MPI_COMM_WORLD, -1);
    }
    else if (counts[5] < 1)
    {
        fprintf(stderr, "Rank %d did not print 1 d.\n", rank);
        MPI_Abort(MPI_COMM_WORLD, -1);
    }


    fclose(file);

    PMPI_Finalize();

    return 0;
}
