#include "src.hpp"

int test_main(int argc, char* argv[])
{
    char* buffer;
    size_t size = 0;

    FILE* stream = open_memstream(&buffer, &size);
    int stdout_handle = dup(fileno(stdout));
    dup2(fileno(stream), fileno(stdout));

    main(argc, argv);

    fflush(stdout);
    dup2(stdout_handle, fileno(stdout));
    close(stdout_handle);
    fclose(stream);

    if (len(buffer) < 11 * num_procs)
    {
        fprintf(stderr, "Did not print out hello world on each process.  Make sure all processes print hello world\n");
        return -1;
    }
    return 0;
}
