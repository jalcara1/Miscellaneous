#include <mpi.h>
#include <math.h>
#include <stdio.h>

long double integral(long double rankIntgL, long double rankIncrL, int rankIncrN){
  
  long double midPoint, intg =0;
  for(int j =0; j< rankIncrN; j++){
    midPoint = rankIntgL + (j +0.5) *rankIncrL; // Mid-Point
    intg += cos(midPoint) *rankIncrL;
  }
  return intg;
}
int main(int argc, char** argv){

  int incrN, tasks, rank;
  long double incrL, sumIntegral, intgL, intgU, rankIntgL, pi, rankIntegral, bufGather[64];

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &tasks);
  
  pi = 3.141592653589793238;
  intgL = 0; //Integration Lower
  intgU = (pi *1) /2; //Integration Upper
  incrN = 500; // Process Increment Number
  incrL = ((intgU -intgL) /incrN) /tasks; // Increment Length

  rankIntgL = intgL +rank *incrN *incrL;  // Integration Lower  for Partition Rank
  rankIntegral = integral(rankIntgL, incrL, incrN);

  printf("Partial Process %d Sum %.64Lf \n", rank, rankIntegral);
  //Gathers values from a group of processes
  //MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)    
  MPI_Gather(&rankIntegral, 1, MPI_LONG_DOUBLE, bufGather, 1, MPI_LONG_DOUBLE, 0, MPI_COMM_WORLD);

  if(rank == 0) {
    sumIntegral = 0;
    for (int i =0; i< tasks; i++) {
      sumIntegral += bufGather[i];
    }
    printf("The Integral= %.64Lf\n", sumIntegral);
  }
  MPI_Finalize();
  return 0;
}
