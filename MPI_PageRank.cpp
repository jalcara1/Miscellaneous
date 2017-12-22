#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <mpi.h>
using namespace std;

int main(int argc, char** argv){
  if(argc < 4){
    cerr << "Usage: " << argv[0] << " SIZE DENSITY TOLERANCE" << endl;
    return 1;
  }
  int size = atoi(argv[1]), numProc, idProc, i, j, next =1;
  int density = atoi(argv[2]), links = ((size*size)/100)*density;
  float tolerance = atof(argv[3]);
  
  MPI_Status info;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numProc);
  MPI_Comm_rank(MPI_COMM_WORLD, &idProc);

  int job = size/(numProc-1);
  if(idProc == 0){
    float **stochasticM, *PageRank, *X;
    stochasticM = new float* [size];
    PageRank = new float [job];
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
    index = new int  [links];
    ptr = new int  [size+1];
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
    bool send = false;
    for(i =0; i< numProc; ++i){
      MPI_Send(&data[0], links, MPI_FLOAT, i, 0, MPI_COMM_WORLD);
      MPI_Send(index, links, MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Send(X, size, MPI_FLOAT, i, 0, MPI_COMM_WORLD);
      MPI_Send(ptr, (size+1), MPI_INT, i, 0, MPI_COMM_WORLD);
    }
    do{
      if(send){
	for(i =0; i< numProc; ++i){
	  MPI_Send(X, size, MPI_FLOAT, i, 0, MPI_COMM_WORLD);
	}
      }
      int pos =0;
      float out =0, subtract =0, val =0;
      for(i =1; i< numProc; ++i){
	MPI_Recv(PageRank, job, MPI_FLOAT, i, 0, MPI_COMM_WORLD, &info);
	for(j =0; j< job; ++j){
	  cout.precision(10);
	  cout << fixed;    
	  cout << "Page " << i << " Rank: " << PageRank[i] << endl;
	  out += PageRank[i];
	  val = fabs(PageRank[j]-X[pos]);
	  X[pos] = PageRank[j];
	  pos++;
	  if(val > subtract){
	    subtract = val;
	  }	      
	}
      }
      cout << tolerance << " :: " << subtract << endl;
      if(subtract < tolerance){
	next =0; //Check Range By Any Proc
      }
      for(i =0; i< numProc; ++i){
	MPI_Send(&next, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
      }
      cout << "::Sum " << out << endl;
      send = true;
    }while(next);
  }else{
    float *data, *X, *resultJob;
    int *index, *ptr, k1, k2, pos =0, cont;
    bool receive = false;
    data = new float[links];
    X = new float[size];
    index = new int[links];
    ptr = new int[size+1];      
      
    MPI_Recv(data, links, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &info);
    MPI_Recv(index, links, MPI_INT, 0, 0, MPI_COMM_WORLD, &info);
    MPI_Recv(X, size, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &info);
    MPI_Recv(ptr, (size+1), MPI_INT, 0, 0, MPI_COMM_WORLD, &info);
      
    do{
      if(receive){
	MPI_Recv(X, size, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &info);
      }
      pos =0;
      for(i =(idProc-1)*job; i< ((idProc-1)*job)+job; ++i){
	k1 = ptr[i];
	k2 = ptr[i+1];
	cont =0;
	for(j =k1; j< k2; ++j){
	  resultJob[pos] += (float)data[j]*X[index[j]]; 
	}
	pos++;    
      }
      MPI_Send(resultJob, job, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
      MPI_Recv(&next, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &info);
      receive = true;
    }while(next);
  }
  MPI_Finalize();
  return 0;
}
