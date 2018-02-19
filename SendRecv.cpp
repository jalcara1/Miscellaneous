#include "stdio.h"
#include "mpi.h"

int main(int argc, char** argv){

  int rank, dataSize =3, src =0, dest =1, tag =0;
  int data[] = {1,2,3},
    
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(rank == 0)
    MPI_Send(data, dataSize, MPI_INT, dest, tag, MPI_COMM_WORLD);
  if(rank == 1){
    MPI_Recv(data, dataSize, MPI_INT, src, tag, MPI_COMM_WORLD, &status);
    printf("Data[0] = %d\n", data[0]);
    printf("Data[1] = %d\n", data[1]);
    printf("Data[2] = %d\n", data[2]);
  }
  MPI_Finalize();
  return 0;
}
