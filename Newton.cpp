#include <iostream>
#include <iomanip>
using namespace std;

int main(){
  float x[10], y[10], p[10], k, f, f1=1,f2=0;
  int n,i,j=1;
  cout << "Enter the number of observations:" << endl;
  cin >> n;

  cout << "Enter the different values of x:" << endl;
  for (i=1;i<=n;i++)
    cin >> x[i];

  cout << "The corresponding values of y are:" << endl;
  for (i=1;i<=n;i++)
    cin >> y[i];

  f=y[1];
  cout << "Enter the value of 'k' in f(k) you want to evaluate:" << endl;
  cin >> k;

  do{
    for (i=1;i<=n-1;i++){
      p[i] = ((y[i+1]-y[i])/(x[i+j]-x[i]));
      y[i]=p[i];
    }
    f1=1;
    for(i=1;i<=j;i++){
      f1*=(k-x[i]);
    }
    f2+=(y[1]*f1);
    n--;
    j++;
  }while(n!=1);
  f+=f2;
  std::cout.precision(20);
  std::cout << std::fixed;
  std::cout << "Valor: " << f << std::endl;
  return 0;
}
