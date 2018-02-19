#include "stdio.h"
#include "stdlib.h"
#include "omp.h"
using namespace std;

int main(int argc, char** argv){
  int Threads = omp_get_max_threads();
  
#pragma omp parallel num_threads(Threads)
  {
    int ID = omp_get_thread_num();
    for(int x =0; x< ID; ++x){
      printf("x = %d Thread = %d\n", x, omp_get_thread_num());
    }
  }


  return 0;
}
