#include "luafc.h"

using namespace std;

int main(){
 time_t time_start, time_B, time_H;
 int N=1;
 double **H;
 double **B;
 double **C;

 while(1.0*N/2.0 != N/2 || N==0){
  cout<<"N value: ";
  cin>> N;
  if(1.0*N/2.0 != N/2 || N==0){
   cout<<"N must be a postitive, even integer.\n\n";
  }
 }
 
 time_start = time(0);

 Allocate2doub(&H,N,N);

 illHilbert(&H,N,N,0);

 ofstream holdout;
 holdout.open("OUTPUT/.Q3Hillbert.txt");
 holdout<<N<<"\n";
 WriteMat(H,N,N,holdout);
 
 time_H = difftime(time(0),time_start);
 holdout<<time_H<<"\n";

 holdout.close();
/*****************/
 time_start = time(0);

 Allocate2doub(&B,N,N);
 
 BinomMat(&B,N,N,0);

 holdout.open("OUTPUT/.Q3Binomial.txt");
 holdout<<N<<"\n";
 WriteMat(B,N,N,holdout);

 time_B = difftime(time(0),time_start);
 holdout<<time_B<<"\n";

 holdout.close();
 
 Deallocate2doub(&H,N);
 Deallocate2doub(&B,N);
}
