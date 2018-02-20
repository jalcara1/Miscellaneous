#include <iostream>
#include "mpi.h"
using namespace std;

int main(int argc, char *argv[]){
  int rankId, tasks;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rankId);
  MPI_Comm_size(MPI_COMM_WORLD, &tasks);
  
  //gethostname(host, hostSize);
  printf("The process number %d of %d, ¡Says Hello! \n", rankId, tasks);

  MPI_Finalize();
  return 0;
}
