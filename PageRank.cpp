#include <iostream>
#include <cstdlib> //srand, rand
using namespace std;

typedef long double ld;
typedef unsigned long long ll;
const int MAXN = 10;

int main(void){
  ld** stochasticM; // Stochastic Matrix With The Pages Links
  stochasticM = new ld* [MAXN];
  ll Fu =0; //Forward-Links
  ll pages =0; //Number Of Forward-Links By One Page
  srand(time(NULL));
  for(ll i =0; i< MAXN; ++i){
    stochasticM[i] = new ld[MAXN];
    for(ll j =0; j< MAXN; ++j){
      stochasticM[i][j] = 0;
    }
  }  
  for(ll i =0; i< MAXN; ++i){
    pages = 1 + rand()%MAXN;
    for(ll j =0; j< pages; ++j){          
      do{
	Fu = 0 + rand()%(MAXN);
      }while(Fu == i);
      stochasticM[Fu][i] += 1/(ld)pages;
    }
  }
  for(ll i =0; i< MAXN; ++i){
    for(ll j =0; j< MAXN; ++j){
      cout << stochasticM[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}
