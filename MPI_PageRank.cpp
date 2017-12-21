#include <iostream>
#include <cstdlib>
#include <ctime>
//#include <mpi.h>

using namespace std;

int main(int argc, char** argv){
  if(argc < 4){
    cerr << "Usage: " << argv[0] << " SIZE DENSITY TOLERANCE" << endl;
    return 1;
  }
  int size = atoi(argv[1])/*, numProc, idProc*/, i, j;
  int density = atoi(argv[2]), links = ((size*size)/100)*density;
  float tolerance = atof(argv[3]);
  /*
  MPI_Status info;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numProc);
  MPI_Comm_rank(MPI_COMM_WORLD, &idProc); 
  */
  float **stochasticM, *PageRank, *X;
  stochasticM = new float* [size];
  PageRank = new float [size];
  X = new float [size];
  int Fx = links/size /*Forward-Links*/, Fu /*Forward-Link*/;

  srand((unsigned)time(0));
  
  for(i =0; i< size; ++i){
    stochasticM[i] = new float [size];
    for(j =0; j< size; ++j){
      stochasticM[i][j] = 0;
    }
    X[i] = (float)1/size;
  }
  for(i =0; i< size; ++i){
    for(j =0; j< Fx; ++j){      
      do{
	Fu = rand()%size;
      }while(Fu == i); // Check Condition
      stochasticM[Fu][i] += (float)1/Fx;
    }
  }
  /*--- Transform stochasticM in CSR Matriz(Compressed Sparse Row) ---*/
  int *index, *ptr;
  float *data;
  index = new int [links];
  ptr = new int [size+1];
  data = new float [links];
  int indexP =0, ptrP =0, dataP =0; // Vectors Positions
  bool first = true;
  for(i =0; i< size; ++i){
    for(j =0; j< size; ++j){
      if(stochasticM[i][j] != 0){
	data[dataP] = (float)stochasticM[i][j];
	index[indexP] = j;
	if(first){
	  first = false;
	  ptr[ptrP] = dataP;	 
	  ptrP++;
	}
	dataP++;
	indexP++;
      }
    }
    first = true;
  }
  ptr[ptrP] = links;
  int k1, k2, pos =0, cont;
  for(i =0; i< size; ++i){
    k1 = ptr[i];
    k2 = ptr[i+1];
    cont =0;
    for(j =k1; j< k2; ++j){
      PageRank[pos] += (float)data[j]*X[index[j]]; 
    }
    pos++;    
  }
  float out =0;
  for(i =0; i< size; ++i){
    out += (float)PageRank[i];
    cout << "Page " << i << " Rank: " << PageRank[i] << endl;
  }
  cout << "--> " << out << endl;
  //MPI_Finalize();
  return 0;
}
