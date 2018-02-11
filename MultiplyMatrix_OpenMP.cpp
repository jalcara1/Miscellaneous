#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#define MAXN 1000

long long A[MAXN][MAXN], B[MAXN][MAXN], C[MAXN][MAXN]; // declaring matrices of MAXNxMAXN size
int main(){
  int i, j, m; // Indices matrix multiplication
  float timer; // Time measures
  clock_t clock1, clock2;

  srand ( time(NULL) );
  for(i=0;i<MAXN;i++) {
    for(j=0;j<MAXN;j++) {
      A[i][j]= (rand()%100 + 1);
      B[i][j]= (rand()%100 + 1);
    }
  }
  printf("Max threads: %i \n",omp_get_max_threads());
#pragma omp parallel
  printf("Number threads: %i \n",omp_get_num_threads());
  clock1=time(NULL); // Time measure
#pragma omp parallel for private(m,j)
  for(i =0; i< MAXN; i++) {
    for(j =0; j< MAXN; j++) {
      C[i][j] =0.; // Set initial value of resulting matrix C = 0
      for(m =0; m< MAXN; m++) {
	C[i][j] = A[i][m] * B[m][j] + C[i][j];
      }
    }
  }
  clock2=time(NULL); // Time measure
  timer = (float)(clock2-clock1); // Time elapsed for job row-wise
  printf("Time: %f \n",timer);
  return 0;
}
