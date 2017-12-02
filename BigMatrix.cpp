#include <iostream>
using namespace std;

typedef unsigned long long ll;
const ll MAXN = 100000;

int main(void){
  ll** matriz;
  matriz = new ll* [MAXN];

  for(ll i =0; i< MAXN; ++i){
    matriz[i] = new ll[MAXN];
    for(ll j =0; j< MAXN; ++j){
      matriz[i][j] = 1;
      //cout << matriz[i][j] << "  ";
    }
    //cout << endl;
  }
  return 0;
}
