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

    char buffer[256];
    char rank_str[16];  // buffer to hold the string version
    snprintf(rank_str, sizeof(rank_str), "%d", rank);
    int found = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        if (strstr(buffer, rank_str) != NULL) {
            found = 1;
            break;
        }
    }

    if (!found)
    {
        fprintf(stderr, "Rank %d did not find it's rank ID.  Make sure you are printing both Hello World and the rank to pass Tutorial 01.\n", rank);
        MPI_Abort(MPI_COMM_WORLD, -1);
    }

    fclose(file);

    PMPI_Finalize();

    return 0;

