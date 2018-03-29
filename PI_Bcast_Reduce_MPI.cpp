#include "mpi.h"
#include <stdio.h>
#include <math.h>

int main(int argc, char** argv){
  
  int n =0, rank, tasks;
  long double myPi, pi, h, sum, x;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&tasks);

  if(rank ==0){
    n = 1024*tasks;
  }  
  //Send message from "root" rank to all other processes
  //MPI_Bcast(void* data, int count, MPI_Datatype datatype, int root, MPI_Comm communicator)
  MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
  h = 1.0 / (long double) n; //Steps
  sum =0.0;
  for(int i =rank +1; i<= n; i += tasks){
    x = h * ((long double)i -0.5);
    sum += 4.0 / (1.0 + x*x);
  }
  myPi = h * sum;
  //Set a single value from values on all processes -> MPI_Op op = Operation
  //MPI_Reduce(void* send_data, void* recv_data, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm communicator)
  MPI_Reduce(&myPi, &pi, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  if(rank ==0){
    printf("PI -->>  %.64Lf\n", pi);
  }
  MPI_Finalize();
  return 0;
}
