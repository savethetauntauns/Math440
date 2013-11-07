#include "luafc.h"

using namespace std;

int main(){
 time_t time_dur, time_end;
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
 
 time_t time_start = time(0);

 Allocate2doub(&H,N,N);
 Allocate2doub(&B,N,N);
 Allocate2doub(&C,N,N);

 illHilbert(&H,N,N,0);
 BinomMat(&B,N,N,0);
 MultiMat(&C, B, H, N, N);
 
// For Output of entire matrix:
/* 
 OutputMat(H,N,N);
cout<<endl;
 OutputMat(B,N,N);
cout<<endl;
 OutputMat(C,N,N);
*/

 time_end = time(0);
 time_dur = difftime(time_end,time_start);

// For time output and matrix samples
 cout<<"N\tC[N/2][N/2]\t\tC[N][N]\t\ttime"<<endl;
 cout<<N<<"\t"<<C[N/2-1][N/2-1]<<"\t\t"<<C[N-1][N-1]<<"\t\t"<<time_dur<<endl;


 Deallocate2doub(&H,N);
 Deallocate2doub(&B,N);
 Deallocate2doub(&C,N);
}
