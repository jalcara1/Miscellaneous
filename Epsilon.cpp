#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char *argv[]){

  cout << "quadruple precision\t" << "Single precision\n" << endl;
  int count = 0;
  float d = 0.5;
  long double e = 0.5;

  while(1 != 1 + e) {
    if(1 != 1 + d){
      cout << setprecision(14) << "Iteration " << count << " = " << e << "\t";
      cout << setprecision(7) << "Iteration " << count << " = " << d << endl;
      d = d / 2;
    }else{
      cout << setprecision(14) << "Iteration " << count << " = " << e << endl;
    }
    e = e / 2;
    count++;
  }
  return 0;
}
