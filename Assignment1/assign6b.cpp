#include "luafc.h"

using namespace std;

int main(){
 time_t t_1, t_2, t_3, t_4, t_new, time_total,t, t_w;
 int N;
 double **C;

 time_t time_start = time(0);

 ifstream holdin;
 
 holdin.open("OUTPUT/.Q6UpperLeft.txt");
 Allocate2doub(&C,N,N);
 holdin >> N;
 ReadMat(&C,N,holdin,0,0);
 holdin >> t_1;
 holdin.close();

 holdin.open("OUTPUT/.Q6UpperRight.txt");
 holdin >> N;
 ReadMat(&C,N,holdin,0,N);
 holdin >> t_2;
 holdin.close();

 holdin.open("OUTPUT/.Q6LowerLeft.txt");
 holdin >> N;
 ReadMat(&C,N,holdin,N,0);
 holdin >> t_3;
 holdin.close();

 holdin.open("OUTPUT/.Q6LowerRight.txt");
 holdin >> N;
 ReadMat(&C,N,holdin,N,N);
 holdin >> t_4;
 holdin >> t_w;
 holdin.close();
 
 t_new = difftime(time(0),time_start);
 if( t_1>t_2){
   if(t_1>t_3){
     if(t_1>t_4){
	t=t_1;
     }
     else{
        t=t_4;
     }
   }
   else if(t_3>t_4){
     t=t_3;
   }
   else{
     t=t_4;
   }
 }
 else if(t_2>t_3){
   if(t_2>t_4){
     t=t_2;
   }
   else{
     t=t_4;
   }
 }
 else if(t_3>t_4){
   t=t_3;
 }
 else{
   t=t_4;
 }
 time_total=t_new+t+t_w;    

 cout<<"N\tC[N/2][N/2]\tC[N][N]\tT_comp\tT_Read\tT_write\ttime_total\n";
 cout<<2*N<<"\t" <<C[N-1][N-1]<<"\t"<<C[2*N-1][2*N-1]<<"\t"<<t<<"\t"<<t_new<<"\t"<<t_w<<"\t"<<time_total<<"\t"<<time_total<<"\n";
 
 Deallocate2doub(&C,N);

}
