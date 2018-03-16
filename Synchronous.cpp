#include "stdio.h"
#include "mpi.h"

MPI_Status status;

int main(int argc, char** argv){

  int rank, tasks, src =0, tag =0, dest=0, dataSize = 1; 
    
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &tasks);

  char word = 'T';

  if(rank != 0){
    char rec_buf;
    MPI_Recv(&rec_buf, dataSize, MPI_CHAR, src, tag, MPI_COMM_WORLD, &status);
    printf("Process %d recived from %d: %d\n", rank, src, rec_buf);
  }
  
  MPI_Send(&word, dataSize, MPI_CHAR, dest, tag, MPI_COMM_WORLD);

  if(rank == 0){
    char rec_buf;
    MPI_Recv(&rec_buf, dataSize, MPI_CHAR, src, tag, MPI_COMM_WORLD, &status);
    printf("Process %d recived from %d: %d\n", rank, src, rec_buf);
  }
  
  MPI_Finalize();
  return 0;
}
