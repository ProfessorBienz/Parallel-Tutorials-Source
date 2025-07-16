#ifndef TUTORIAL_SRC_HPP
#define TUTORIAL_SRC_HPP

#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"

bool mpi_initialized;
bool mpi_finalized;
bool print
int mpi_num_procs;

int __wrap_MPI_Init(int* argc, char*** argv);
int __wrap_MPI_Finalize();
int __wrap_printf(const char * format, ...);


#endif
