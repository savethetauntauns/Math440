#include "mpi.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include "time.h"
using namespace std;

int main( int argc , char* argv[] ){

//Initialization with Common Variables on all cores
 MPI::Init(argc,argv);
 MPI::Status status;
 
 time_t startt;
 int myrank=MPI::COMM_WORLD.Get_rank();
 int psize=MPI::COMM_WORLD.Get_size();
 int J;
 
//MASTER CORE
 if(myrank==0){
 //Initialization of master core and UI
  cout<<"This program runs step 1 from Assignment 4 and requires an input of J.\n\n";
  cout<<"J:\t";
  cin>>J;
 startt=time(0);
//Sending J so that every core has input
  for(int i=1 ; i<psize ; i++){
   MPI::COMM_WORLD.Send(&J,1,MPI::INT,i,100+i);
  }
 }

//CORES 1 -> P Receiving J
 if(myrank!=0){
  MPI::COMM_WORLD.Recv(&J,1,MPI::INT,0,100+myrank);
 }
//Creation and allocation of vector rk
 double *rk;
 rk=new double[J]; 
 double **X;
 X=new double*[J]; 
 double *x;
 x=new double[J]; 
 for(int i=0 ; i<J ; i++){
  rk[i]= (double)(1.0*rand()/(1.0*RAND_MAX));
  rk[i]*=(((1.0*i+1.0)*(1.0*myrank+1.0))-(myrank*1.0+1)/(i*1.0+1.0))+((1.0*myrank+1.0)/(i+1.0));
 }

//Creation and allocation of vector X, x
 for(int i=0; i<J ; i++){
  X[i]=new double[J*psize];
  for(int j=0;j<J*psize;j++){ 
   X[i][j]= (double)(1.0*rand()/(1.0*RAND_MAX));
   X[i][j]*=((((i+1.0)*1.0+J*myrank*1.0)*(1.0*j+1.0))+((i+1.0)*1.0+J*myrank*1.0)/(j*1.0+1.0))-((i+J*myrank+1.0)*(j+1.0)*1.0);
   x[i]+=X[i][j];
  }
  x[i]*=1/(J*psize);
 }
 
 double *w;
 w=new double[psize*J];

//CORES 1 -> P Sending rk to master
 if(myrank!=0){
  MPI::COMM_WORLD.Send(rk,J,MPI::DOUBLE,0,200+myrank);
 }

//MASTER Receiving vectors
 if(myrank==0){
  double **allrk;
  allrk=new double*[psize];
  for(int i=0;i<psize;i++){
   allrk[i]=new double[J];
   if(i==0){
    for(int j=0;j<J;j++){
     allrk[i][j]=rk[j];
    }
   }
   else{
    MPI::COMM_WORLD.Recv(allrk[i],J,MPI::DOUBLE,i,200+i);
   }
  }
  double rsum(0);
  double xsum(0);
  for(int i=0; i<psize;i++){
   for(int j=0; j<J;j++){
    rsum+=allrk[i][j];
   }
  }
  for(int i=0; i<psize;i++){
   for(int j=0; j<J;j++){
    w[i*J+j]=allrk[i][j]/rsum;
   }
  }
  for(int i=0; i<psize;i++){
   MPI::COMM_WORLD.Send(w, J*psize, MPI::DOUBLE,i,400+i);
  }
/*  for(int i=0;i<psize;i++){
   delete[] allrk[i];
  }
  delete[] allrk;*/
 }


 if(myrank!=0){
  MPI::COMM_WORLD.Recv(w, J*psize,MPI::DOUBLE,0,400+myrank);
 }
 double **Y;
 Y=new double*[J];
 for(int i=0;i<J;i++){
  Y[i]=new double[J*psize];
  for(int j=0;j<J*psize;j++){
   Y[i][j]=0;
  }
 }

 for(int i=0;i<J;i++){
  for(int j=0;j<J*psize;j++){
   Y[i][j]=sqrt(w[j])*(X[i][j]-x[i]);
   Y[i][j]=Y[i][j]/(1-w[j]);
  }
 }
 double **y;
 y=new double*[J*psize];
 for(int i=0;i<J*psize;i++){
  y[i]=new double[J*psize];
 }
 
 if(myrank!=0){
  for(int i=0;i<J;i++){
   MPI::COMM_WORLD.Send(&i, 1, MPI::INT, 0, myrank*10000+i);
   MPI::COMM_WORLD.Send(Y[i], J*psize, MPI::DOUBLE, 0, myrank*100000+i);
  }
 }
 if(myrank==0){
  int loc;
  for(int i=1; i<psize; i++){
   for(int j=0;j<J;j++){
    MPI::COMM_WORLD.Recv(&loc, 1, MPI::INT, i, i*10000+j);
    MPI::COMM_WORLD.Recv(y[J*(i)+loc], J*psize, MPI::DOUBLE, i, 100000*i+j);
   }
  }
  for(int j=0;j<J;j++){
   for(int i=0; i<J*psize; i++){
    y[j][i]=Y[j][i];
   }
  }
 }
 for(int i=0 ; i<J*psize; i++){
  MPI::COMM_WORLD.Bcast(y[i],J*psize,MPI::DOUBLE,0);
 }
 double **C;
 C=new double*[J];
 for(int i=0; i<J ; i++){
  C[i]=new double[J*psize];
 }
 double cmin(100000), cmax(0);
 for(int i=0; i<J ; i++){
  for(int j=0; j<J*psize ; j++){
   for(int k=0; k<J*psize ; k++){
      C[i][j]+=y[J*myrank+i][k]*y[k][j];
   }
  if(C[i][j]>cmax)
   cmax=C[i][j];
  if(C[i][j]<cmin)
   cmin=C[i][j];
  }
 }
/*
 if(myrank!=0){
  for(int i=0;i<J;i++){
   MPI::COMM_WORLD.Send(&i, 1, MPI::INT, 0, myrank*100000+i*10);
   MPI::COMM_WORLD.Send(C[i], J*psize, MPI::DOUBLE, 0, myrank*10000+i*10);
  }
 }
*/
 if(myrank!=0){
  MPI::COMM_WORLD.Send(&cmax,1,MPI::DOUBLE,0,myrank);
  MPI::COMM_WORLD.Send(&cmin,1,MPI::DOUBLE,0,myrank*10);
 }
 if(myrank==0){
  double **chold;
  chold=new double*[psize];
  for(int i=0; i<psize; i++){
   chold[i]=new double[2];
   if(i==0){
    chold[i][0]=cmax;
    chold[i][1]=cmin;
   }else{
    MPI::COMM_WORLD.Recv(&chold[i][0],1,MPI::DOUBLE,i,i);
    MPI::COMM_WORLD.Recv(&chold[i][1],1,MPI::DOUBLE,i,i*10);
   }
  }
  double alln(cmin),allm(cmax);
  for(int i=0; i<psize;i++){
   if(chold[i][0]>allm)
    allm=chold[i][0];
   if(chold[i][1]<alln)
    alln=chold[i][1];
  }
  cout<<"MAX\t\tMIN\t\tTIME\n";
  cout<<allm<<"\t"<<alln<<"\t"<<time(0)-startt<<endl;
 }
/* if(myrank==0){
  int loc;
  double **c; 
  c=new double*[psize*J];
  for(int i=0; i<psize*J; i++){
   c[i]=new double[psize*J];
  }
  for(int i=1; i<psize; i++){
   for(int j=0;j<J;j++){
    MPI::COMM_WORLD.Recv(&loc, 1, MPI::INT, i, i*100000+10*j);
    MPI::COMM_WORLD.Recv(c[J*(i)+loc], J*psize, MPI::DOUBLE, i, 10000*i+10*j);
   }
  }
  for(int j=0;j<J;j++){
   for(int i=0; i<J*psize; i++){
    c[j][i]=C[j][i];
   }
  }
  cout<<"c[0][0]\t\tc[J][J]\t\tc[psize*J][psize*J]\t\ttime(sec)\n";
  cout<<c[0][0]<<"\t"<<c[J][J]<<"\t"<<c[psize*J-1][psize*J-1]<<"\t"<<time(0)-startt<<endl;
 }
*/
 delete[] rk;
 delete[] x;
 delete[] w;
 for(int i=0;i<J;i++){
  delete[] C[i];
  delete[] Y[i];
  delete[] X[i];
 }
 delete[] C;
 delete[] Y;
 delete[] X;
 MPI::Finalize();
}
