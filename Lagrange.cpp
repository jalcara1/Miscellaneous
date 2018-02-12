#include <iostream>
#include <iomanip>
using namespace std;

#define MAXN 50

int main(){
  double x[MAXN],y[MAXN],z,l, valor=0;
  int n;
  cout<<"Elementos: "; cin>>n;
  cout << "x: ";
  for(int i=0; i<n; i++){
    cin >> x[i];
  }//p(x)=L0(x)f(x0)+L1(x)f(x1)+L2(x)f(x2)+L3(x)f(x3)+L4(x)f(x4)
  cout << "\nF(x): ";
  for(int i=0; i<n; i++){
    cin >> y[i];
  }//L0(x)=(x−x1)(x−x2)(x−x3)(x−x4)/(x0−x1)(x0−x2)(x0−x3)(x0−x4)
  cout << "\nPunto: ";
  cin >> z;
  for(int i=0; i<n ;i++){
    l = y[i];
    for(int j=0; j<n; j++){
      if(i!=j){
	l *= (z-x[j]) / (x[i]-x[j]);
      }
    }
    valor = valor+l;
  }//L1(x)=(x−x0)(x−x2)(x−x3)(x−x4)/(x1−x0)(x1−x2)(x1−x3)(x1−x4)
  std::cout.precision(20);
  std::cout << std::fixed;
  std::cout << "Valor: " << valor << std::endl;

  return 0;
}
