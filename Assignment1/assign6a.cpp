#include "luafc.h"

using namespace std;

int main(){
 time_t time_start, time_1, time_2, time_3, time_4,time_w;
 int N=1;
 double **H1, **H2, **H3, **H4;
 double **B1, **B2, **B3, **B4;
 double **C1, **C2, **C3, **C4;

 while(1.0*N/2.0 != N/2 || N==0){
  cout<<"N value: ";
  cin>> N;
  if(1.0*N/2.0 != N/2 || N==0){
   cout<<"N must be a postitive, even integer.\n\n";
  }
 }
 
 time_start = time(0);

 Allocate2doub(&H1,N/2,N);
 illHilbert(&H1,N/2,N,0);
 Allocate2doub(&B1,N,N/2);
 BinomMat(&B1,N,N/2,0);
 Allocate2doub(&C1,N/2,N/2);
 MultiMat(&C1,H1,B1,N/2,N);
 Deallocate2doub(&H1,N/2);
 Deallocate2doub(&B1,N);
 time_1=difftime(time(0),time_start);
 
 time_start = time(0);
 Allocate2doub(&H2,N/2,N);
 illHilbert(&H2,N/2,N,0);
 Allocate2doub(&B2,N,N/2);
 BinomMat(&B2,N,N/2,N/2);
 Allocate2doub(&C2,N/2,N/2);
 MultiMat(&C2,H2,B2,N/2,N);
 Deallocate2doub(&H2,N/2);
 Deallocate2doub(&B2,N);
 time_2=difftime(time(0),time_start);

 time_start = time(0);
 Allocate2doub(&H3,N/2,N);
 illHilbert(&H3,N/2,N,N/2);
 Allocate2doub(&B3,N,N/2);
 BinomMat(&B3,N,N/2,0);
 Allocate2doub(&C3,N/2,N/2);
 MultiMat(&C3,H3,B3,N/2,N);
 Deallocate2doub(&H3,N/2);
 Deallocate2doub(&B3,N);
 time_3=difftime(time(0),time_start);
 
 time_start = time(0);
 Allocate2doub(&H4,N/2,N);
 illHilbert(&H4,N/2,N,N/2);
 Allocate2doub(&B4,N,N/2);
 BinomMat(&B4,N,N/2,N/2);
 Allocate2doub(&C4,N/2,N/2);
 MultiMat(&C4,H4,B4,N/2,N);
 Deallocate2doub(&H4,N/2);
 Deallocate2doub(&B4,N);
 time_4=difftime(time(0),time_start);
 
 time_start = time(0);
 ofstream holdout;
 
 holdout.open("OUTPUT/.Q6UpperLeft.txt");
 holdout<<N/2<<"\n";
 WriteMat(C1,N/2,N/2,holdout);
 Deallocate2doub(&C1,N/2);
 holdout<<time_1<<"\n";
 holdout.close();
 holdout.open("OUTPUT/.Q6UpperRight.txt");
 holdout<<N/2<<"\n";
 WriteMat(C2,N/2,N/2,holdout);
 Deallocate2doub(&C2,N/2);
 holdout<<time_2<<"\n";
 holdout.close();
 holdout.open("OUTPUT/.Q6LowerLeft.txt");
 holdout<<N/2<<"\n";
 WriteMat(C3,N/2,N/2,holdout);
 Deallocate2doub(&C3,N/2);
 holdout<<time_3<<"\n";
 holdout.close();
 holdout.open("OUTPUT/.Q6LowerRight.txt");
 holdout<<N/2<<"\n";
 WriteMat(C4,N/2,N/2,holdout);
 Deallocate2doub(&C4,N/2);
 holdout<<time_4<<"\n";
 time_w=difftime(time(0),time_start);
 holdout<<time_w<<"\n";
 holdout.close();
 cout<<"N\tT_write\n";
 cout<<N<<"\t"<<time_w<<"\n";
}
