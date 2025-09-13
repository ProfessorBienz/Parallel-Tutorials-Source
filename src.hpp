#ifndef TUTORIAL_SRC_HPP
#define TUTORIAL_SRC_HPP

#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern bool mpi_initialized;
extern bool mpi_finalized;
extern int mpi_num_procs;

int MPI_Init(int *argc, char ***argv);
int MPI_Finalize();

// Method to edit in tutorial
int tutorial_main(int argc, char* argv[]);
double generate_random();
void generate_random_array(int N, double*);
double time_random_array_generation(int N);

#ifdef __cplusplus
}
#endif

#endif
