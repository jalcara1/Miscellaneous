#include <iostream>
#include "mpi.h"
using namespace std;

int main(int argc, char *argv[]){
  int rank;
  size_t hostSize = 19;
  char host[hostSize];

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  gethostname(host, hostSize);
  printf("The process number %d is running on %s \n", rank, host);

  MPI_Finalize();
  return 0;
}
