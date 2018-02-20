#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

#define N 8 //number of rows and columns in matrix

MPI_Status status;
double a[N][N],b[N][N],c[N][N];

main(int argc, char** argv){

  int tasks, taskId, workers, source, rows, offset;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &taskId);
  MPI_Comm_size(MPI_COMM_WORLD, &tasks);

  workers = tasks-1;
  //Master
  if(taskId == 0){
    srand(time(0));
    for(int i =0; i< N; ++i){
      for(int j =0; j< N; ++j){
	a[i][j] = 1+rand()%(101-1);;
	b[i][j] = 1+rand()%(101-1);;
      }
    }
    //Send matrix data to the worker tasks
    rows = N/workers;
    offset = 0;
    for(int node =1; node<= workers; ++node){
	MPI_Send(&offset, 1, MPI_INT, node, 1, MPI_COMM_WORLD);
	MPI_Send(&rows, 1, MPI_INT, node, 1, MPI_COMM_WORLD);
	MPI_Send(&a[offset][0], rows*N, MPI_DOUBLE,node,1, MPI_COMM_WORLD);
	MPI_Send(&b, N*N, MPI_DOUBLE, node, 1, MPI_COMM_WORLD);
	offset = offset + rows;
      }
    //Wait for results from all worker tasks
    for(int node =1; node<= workers; ++node){
	MPI_Recv(&offset, 1, MPI_INT, node, 2, MPI_COMM_WORLD, &status);
	MPI_Recv(&rows, 1, MPI_INT, node, 2, MPI_COMM_WORLD, &status);
	MPI_Recv(&c[offset][0], rows*N, MPI_DOUBLE, node, 2, MPI_COMM_WORLD, &status);
      }
    printf("Matrix Result:\n");
    for(int i =0; i< N; ++i) {
      for(int j =0; j< N; ++j){
	printf("%6.2f   ", c[i][j]);
      }
      printf ("\n");
    }
  }
  //Compute Nodes
  if (taskId > 0) {
    int source = 0;
    MPI_Recv(&offset, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
    MPI_Recv(&rows, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
    MPI_Recv(&a, rows*N, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);
    MPI_Recv(&b, N*N, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);
    //Matrix multiplication 
    for(int i =0; i< N; i++){
      for(int j =0; j< rows; j++){
	c[j][i] = 0.0;
	for(int k =0; k< N; k++){
	  c[j][i] += a[j][k] * b[k][i];
	}
      }
    }
    MPI_Send(&offset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    MPI_Send(&rows, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    MPI_Send(&c, rows*N, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
  }
  MPI_Finalize();
  return 0;
}
