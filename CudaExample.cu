#include "stdio.h"
#define N 10

//Sum Arrays
__global__ void add(int *x, int *y, int *z){
  int tID = blockIdx.x;
  if (tID < N){
    z[tID] = x[tID] + y[tID];
  }
}
int main(){
  int x[N], y[N], z[N];
  int *dev_x, *dev_y, *dev_z;
  /*Allocates size bytes of linear memory on the device and returns in *devPtr a pointer to the allocated memory.
    -> cudaMalloc ( void** devPtr, size_t size) 
  */
  cudaMalloc((void **) &dev_x, N*sizeof(int));
  cudaMalloc((void **) &dev_y, N*sizeof(int));
  cudaMalloc((void **) &dev_z, N*sizeof(int));
  //Fill Arrays
  for (int i = 0; i < N; i++){
    x[i] = i;
    y[i] = i+i;
  }
  /* Copies count bytes from the memory area pointed to by src to the memory area pointed to by dst,specifies the
     direction of the copy. The memory areas may not overlap.
     -> cudaMemcpy(void* dst, const void* src, size_t count, enum cudaMemcpyKind kind) 
  */
  cudaMemcpy(dev_x, x, N*sizeof(int), cudaMemcpyHostToDevice);
  cudaMemcpy(dev_y, y, N*sizeof(int), cudaMemcpyHostToDevice);
  add<<<N,1>>>(dev_x, dev_y, dev_z);
  cudaMemcpy(z, dev_z, N*sizeof(int), cudaMemcpyDeviceToHost);

  for (int i = 0; i < N; i++){
    printf("%d + %d = %d\n", x[i], y[i], z[i]);
  }
  
  return 0;
}
