#include <iostream>
#include <cstdlib> //srand, rand
#include <cmath>
using namespace std;

typedef long double ld;
typedef unsigned long long ll;
const int MAXN = 10;

int main(void){
  ld** stochasticM; // Stochastic Matrix With The Pages Links
  stochasticM = new ld* [MAXN];
  ld* X;
  ld* PageRank;
  X = new ld[MAXN];
  PageRank = new ld[MAXN];
  /* Forward-Links - Number Of Forward-Links By One Page */
  ll Fu, pages =0, i, j;
  ld tolerance = 0.1, result =0, val, SUMA =0;
  srand(time(NULL));
  for(i =0; i< MAXN; ++i){
    stochasticM[i] = new ld[MAXN];
    X[i] = 1/(ld)MAXN;
    for(j =0; j< MAXN; ++j){
      stochasticM[i][j] = 0;
    }
  }  
  for(i =0; i< MAXN; ++i){
    pages = 1 + rand()%MAXN;
    for(j =0; j< pages; ++j){          
      do{
	Fu = 0 + rand()%(MAXN);
      }while(Fu == i);
      stochasticM[Fu][i] += 1/(ld)pages;
    }
  }
  do{
    for(i =0; i< MAXN; ++i){
      for(j =0; j< MAXN; ++j){
	PageRank[i] += stochasticM[i][j]*X[j];
      }
    }
    for(i =0; i< MAXN; ++i){
      val = abs(PageRank[i]-X[i]);
      if(val > result){
	result = val;
      }
    }
    cout << "->> " << result << endl;
    if(tolerance > result){
      cout << "AQUI" << endl;
      for(i =0; i< MAXN; ++i){
	X[i] = PageRank[i];
      }
    }
  }while(tolerance < result);
  
  for(i =0; i< MAXN; ++i){
    cout << PageRank[i] << endl;
    SUMA += PageRank[i];
    // for(j =0; j< MAXN; ++j){
    //   cout << stochasticM[i][j] << " ";
    // }
    // cout << endl;
  }
  cout << "--»» " << SUMA << endl;
  return 0;
}
