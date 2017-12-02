#include <omp.h>
#include <iostream>
#include <iomanip>
using namespace std;
//g++ -fopenmp PI_OpenMP.cpp -o PI_OpenMP && ./PI_OpenMP
int main(void){
  int Threads = 4;
  unsigned long long num_steps = Threads * 76543210;
  long double pi = 0.0;
  long double step = 1.0/(long double)num_steps; //Rectangles Width 
  unsigned long long cant = num_steps/Threads;
#pragma omp parallel num_threads(Threads)
  {
    int ID = omp_get_thread_num();
    //cout << ID << endl;
    long double x, sum = 0.0;
    for(int i =ID*cant; i< (ID*cant)+cant; ++i){
      x = (i+0.5)*step;
      sum += 4.0/(1.0+x*x);
    }
    pi += step*sum;
  }
  cout.precision(65);
  cout << fixed;
  cout << "PI: " << pi << endl;
  //cout << "-->> " << pi << endl;
  return 0;
}
