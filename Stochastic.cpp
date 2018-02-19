#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef long long ll;
typedef long double ld;

int main(int argc, char** argv){
  if(argc < 4){
    cout << "Usage: " << argv[0] << "SIZE DENSITY TOLERANCE" << endl;
    return 1;
  }
  ll tamanio = atoi(argv[1]);
  ll densidad = atoi(argv[2]);
  ld tolerancia = atof(argv[3]);
  ld **matriz, *vector;
  matriz = new ld* [tamanio];
  vector = new ld [tamanio];
  ll cantidad = ((tamanio*tamanio)*densidad)/100;
  cout << "::* " << cantidad << endl;

  ll noNulos = cantidad/tamanio;
  ll random;
  srand(time(0));
  for(int i = 0; i < tamanio; ++i){
    matriz[i] = new ld [tamanio];
    for(int j = 0; j < tamanio; ++j){
      matriz[i][j] = 0;
    }
    vector[i] = (ld)1/tamanio;
  }
  bool entra =true;
  int salida =0;
  for(int i = 0; i< tamanio; ++i){
    for(int j = 0; j < noNulos; ++j){
      do{
	random = rand()% tamanio;
	if(random != tamanio){
	  entra = false;
	}
      }while(entra);
      matriz[random][i] += (ld) 1/noNulos;
      salida++;
    }
  }
  cout << ":: " << salida << endl;
  double suma =0;
  for(int i = 0; i < tamanio; i++){
    for(int j = 0; j < tamanio; j++){
      cout << matriz[j][i] << "  " ;
      suma += (double)matriz[j][i];
    }
    cout << ":: " << suma << endl;
    suma =0;
  }
  return 0;
}
