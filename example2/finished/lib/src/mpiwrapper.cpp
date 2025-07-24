#include "mpiwrapper.h"

#ifdef __use_mpi
#include <mpi.h>
#endif

int mp_init( int *argc, char ***argv) {
#ifdef __use_mpi
  return MPI_Init(argc, argv);
#else
  return 0;
#endif
}

int mp_finalize(void) {
#ifdef __use_mpi
  return MPI_Finalize();
#else
  return 0;
#endif
}

int mp_comm_rank( int *rank ) {
#ifdef __use_mpi
  return MPI_Comm_rank(MPI_COMM_WORLD, rank);
#else
  *rank = 0;
  return 0;
#endif
}

int mp_comm_size( int *size ) {
#ifdef __use_mpi
  return MPI_Comm_size(MPI_COMM_WORLD, size);
#else
  *size = 0;
  return 0;
#endif
}
