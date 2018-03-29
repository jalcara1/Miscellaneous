#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

//Matrix multiplication kernel - thread specification
__global__
void MatrixMulKernel(float* Md, float* Nd, float* Pd, int width){
  //2D Thread ID
  int tx = threadIdx.x;
  int ty = threadIdx.y;
  //Pvalue stores the Pd element that is computed by the thread
  float Mdelement, Ndelement, Pvalue = 0;
  for(int k = 0; k < width ; ++k){
    Mdelement = Md[ty*width + k];
    Ndelement = Nd[k*width + tx];
    Pvalue += (Mdelement*Ndelement);
  }
  Pd[ty*width + tx] = Pvalue;
}
void MatrixMultiplication(float* M, float* N, float* P, int width){
  int size = width*width*sizeof(float);
  float* Md, *Nd, *Pd;
  //Transfer M and N to device memory
  cudaMalloc((void**)&Md, size);
  cudaMemcpy(Md, M, size, cudaMemcpyHostToDevice);
  cudaMalloc((void**)&Nd, size);
  cudaMemcpy(Nd, N, size, cudaMemcpyHostToDevice);
  //Allocate P on the device
  cudaMalloc((void**)&Pd, size);
  //Setup the execution configuration
  dim3 dimBlock(width, width);
  dim3 dimGrid(1, 1);
  //Launch the device computation threads
  MatrixMulKernel<<<dimGrid,dimBlock>>>(Md, Nd, Pd, width);
  //Transfer P from device to host
  cudaMemcpy(P, Pd, size, cudaMemcpyDeviceToHost);
  //Free device matrices
  cudaFree(Md);
  cudaFree(Nd);
  cudaFree(Pd);
}
int main(){
  const int width = 5;
  float M[width*width], N[width*width], P[width*width];
  srand(time(0));
  for(int i =0; i< (width*width); ++i){
    M[i] = 1+rand()%(101-1);
    N[i] = 1+rand()%(101-1);
    P[i] = 0;
  }
  MatrixMultiplication(M, N, P, width);
  for(int i = 0; i < (width*width) ; ++i){
    printf("%f \n", P[i]);
  }
  return 0;
}
