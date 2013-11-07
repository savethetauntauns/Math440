#include "luafc.h"

using namespace std;

void Allocate2doub(double ***A, int rowsize, int colsize){ 
 *A = new double*[rowsize];
 for(int i=0 ; i < rowsize ; i++){
  (*A)[i] = new double[colsize];
  for(int j=0 ; j < colsize ; j++){
   (*A)[i][j]=0;
  }
 }
}

void Deallocate2doub(double ***A, int rowsize){ 
 for(int i=0 ; i < rowsize ; i++){
  delete [] (*A)[i];
 }
 delete [] *A;
 *A=NULL;
}

void illHilbert(double ***A, int Ns, int N, int startr){
 if(pow((*A)[Ns-1][N-1],2) > 1){
  cout<<"ERROR: Not Allocated Properly\n NOTHING WILL BE RETURNED\n\n";
  return;
 }
 for(int i=0 ; i < Ns ; i++){
  for(int j=0 ; j < N ; j++){
   (*A)[i][j] = (1.0)/((i+j+startr+1)*1.0);
  }
 }
}

void BinomMat(double ***A, int N, int Nc, int startc){
 double b;
 for(int i=0 ; i<N ; i++){
  for(int j=0 ; j<Nc; j++){
   b=pow(-1,i+j+startc)*(i+j+startc+1)*binomcoef(N+i,N-j-startc-1)*binomcoef(N+j+startc,N-i-1)*pow(binomcoef(i+j+startc,i),2);
   if(abs(b)>pow(10,50)||b!=b){
    b=pow(-1,i+j+startc)*(i+j+startc+1)*curcoef(N+i,N-j-1-startc)*curcoef(N+j+startc,N-i-1)*pow(curcoef(i+j+startc,i),2);
   }
   (*A)[i][j]=b;
  }
 }
}

double binomcoef(int n, int k){
 if(n<k){
  return 0;
 }
 long santa = factorial(k)*factorial(n-k);
 return (factorial(n)*1.0/(1.0*santa));
}

double curcoef(int n, int k){
 if(n<k){
  return 0;
 }
 double santa = cos(k)*cos(n-k);
 return (cos(n)*1.0/(1.0*santa));
}

long factorial(int baby){
 long facts = 1;
 if(baby<0){
  return -1;
 }
 else if(baby == 0){
  return facts;
 }
 else{
  for(int i=1 ; i<=baby ; i++){
	facts*=i;
  }
 }
 return facts;
}

void MultiMat(double ***C, double **A, double **B, int xsize, int ysize){
 double  rcprod;
 for(int i=0 ; i<xsize ; i++){
  for(int f=0 ; f<xsize ; f++){
  rcprod=0;
  for(int j=0 ; j<ysize ; j++){
   rcprod += A[i][j] * B[j][f];
  }
  if(rcprod > pow(10,300)||rcprod!=rcprod){
   rcprod = cos(i+f);
  }
  (*C)[i][f]=rcprod;
  }
 }
}

void OutputMat(double **A, int rowsize, int colsize){
 for(int i=0 ; i < rowsize ; i++){
  for(int j=0 ; j < colsize ; j++){
   printf("%E\t", A[i][j]);
  }
  printf("\n");
 }
}

void WriteMat(double **A, int rowsize, int colsize, std::ostream& outfile){
 for(int i=0 ; i < rowsize ; i++){
  for(int j=0 ; j < colsize ; j++){
   outfile << A[i][j] <<"\n";
  }
 }
}

void ReadMat(double ***A, int size, std::istream& infile, int startr, int startc){
 for(int i=0 ; i < size ; i++){
  for(int j=0 ; j < size ; j++){
   infile >> (*A)[i+startr][j+startc];
  }
 }
} 
