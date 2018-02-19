#include "stdio.h"
#include "mpi.h"

const int msg_size = 30;
const int master = 0;
const int master_tag = 0;

int main(int argc, char** argv){

  char msg[msg_size];
  int rank, size;

  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  if(rank == 0){
    for(int proc=1; proc<size; proc++){
      MPI_Recv(msg, msg_size, MPI_CHAR, proc, master_tag, MPI_COMM_WORLD, &status);
      printf(msg);
    }
  }
  else{
    sprintf(msg, "This is process %d\n", rank);
    MPI_Send(msg, msg_size, MPI_CHAR, master, master_tag, MPI_COMM_WORLD);
  }
  MPI_Finalize();
  return 0;
}
