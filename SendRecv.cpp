#include "stdio.h"
#include "mpi.h"

MPI_Status status;

int main(int argc, char** argv){

  int rank, tasks, dataSize =3, src =0, tag =0;
  int data[] = {1,2,3};
    
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &tasks);
  
  if(rank == 0){
    for(int node =1; node<= tasks; ++node){
      MPI_Send(data, dataSize, MPI_INT, node, tag, MPI_COMM_WORLD);
    }
  }else{
    MPI_Recv(data, dataSize, MPI_INT, src, tag, MPI_COMM_WORLD, &status);
    printf("Process %d Data[0] = %d\n", rank, data[0]);
    printf("Process %d Data[1] = %d\n", rank, data[1]);
    printf("Process %d Data[2] = %d\n", rank, data[2]);
  }
  MPI_Finalize();
  return 0;
}
