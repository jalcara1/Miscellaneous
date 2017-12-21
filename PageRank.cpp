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
  ld* sumColum;
  X = new ld[MAXN];
  PageRank = new ld[MAXN];
  sumColum = new ld[MAXN];
  /* Forward-Links - Number Of Forward-Links By One Page */
  ll Fu, pages =0, i, j;
  ld tolerance = 0.1, result =1, val, SUMA =0;
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
  for(i =0; i< MAXN; ++i){
    for(j =0; j< MAXN; ++j){
      sumColum[i] += stochasticM[j][i];
      cout << stochasticM[j][i] << " ";
    }
    cout << "-->>: " << sumColum[i] << endl;
  }
  cout << endl;
  do{
    for(i =0; i< MAXN; ++i){
      for(j =0; j< MAXN; ++j){
	PageRank[i] += stochasticM[i][j]*X[j];
      }
    }
    for(i =0; i< MAXN; ++i){
      val = abs(PageRank[i]-X[i]);
      cout << result << " :: " << val <<endl;
      if(val < result){
	result = val;
      }
    }
    cout << "Result ->> " << result << endl;
    if(tolerance < result){
      cout << "AQUI" << endl;
      for(i =0; i< MAXN; ++i){
	X[i] = PageRank[i];
	cout << X[i] << " ";
      }
      cout << endl;
    }
  }while(tolerance < result)
  for(i =0; i< MAXN; ++i){
    cout << PageRank[i] << endl;
    SUMA += PageRank[i];
  }
  cout << "--»» " << SUMA << endl;
  return 0;
}
