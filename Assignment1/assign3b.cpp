#include "luafc.h"

using namespace std;

 int main(){
 time_t t_b, t_h, t_c, time_total;
 int N;
 double **H;
 double **B;
 double **C;

 time_t time_start = time(0);

 ifstream holdin;
 holdin.open("OUTPUT/.Q3Hillbert.txt");
 holdin >> N;
 Allocate2doub(&H,N,N);
 Allocate2doub(&B,N,N);
 Allocate2doub(&C,N,N);
 
 ReadMat(&H,N,holdin,0,0);
 holdin >> t_h;
 holdin.close();

 holdin.open("OUTPUT/.Q3Binomial.txt");
 holdin >> N;
 ReadMat(&B,N,holdin,0,0);
 holdin >> t_b;
 holdin.close();
 
 MultiMat(&C, H, B, N, N);
 
 t_c = difftime(time(0),time_start);
 time_total = t_b+t_c+t_h;

 cout<<"N\tC[N/2][N/2]\tC[N][N]\ttime_h\ttime_b\ttime_c\ttime_total\n";
 cout <<N<<"\t" <<C[N/2-1][N/2-1]<<"\t"<<C[N-1][N-1]<<"\t"<<t_h<<"\t"<<t_b<<"\t"<<t_c<<"\t"<<time_total<<"\n";
 
 Deallocate2doub(&H,N);
 Deallocate2doub(&B,N);
 Deallocate2doub(&C,N);

}
