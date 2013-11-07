#include "mpi.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

int main( int argc , char* argv[] ){

//Initialization with Common Variables on all cores
 MPI::Init(argc,argv);
 MPI::Status status;
 int myrank=MPI::COMM_WORLD.Get_rank();
 int psize=MPI::COMM_WORLD.Get_size();
 int J;
 
//MASTER CORE
 if(myrank==0){
 //Initialization of master core and UI
  cout<<"This program runs step 1 from Assignment 4 and requires an input of J.\n\n";
  cout<<"J:\t";
  cin>>J;
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
 for(int i=0 ; i<J ; i++){
  rk[i]= (double)(1.0*rand()/(1.0*RAND_MAX));
  rk[i]*=(((1.0*i+1.0)*(1.0*myrank+1.0)+1.0)-(myrank*1.0+1.0)/(i*1.0+1.0))+((1.0*myrank+1.0)/(i+1.0));
 }

 double *rl;
 rl=new double[J*psize]; 

//CORES 1 -> P Sending rk to master
 if(myrank!=0){
  MPI::COMM_WORLD.Send(rk,J,MPI::DOUBLE,0,200+myrank);
 }

//MASTER Receiving vectors
 if(myrank==0){
  double **allrk;
  double *w;
  allrk=new double*[psize];
  w=new double[psize*J];
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
  double sum(0);
  for(int i=0; i<psize;i++){
   for(int j=0; j<J;j++){
    sum+=allrk[i][j];
   }
  }
  for(int i=0; i<psize;i++){
   for(int j=0; j<J;j++){
    w[i*J+j]=allrk[i][j]/sum;
   }
  }
 MPI::COMM_WORLD.Scatter(w, J*psize, MPI::DOUBLE,rl, J*psize, MPI::DOUBLE,0);
 }
 double sum =0;
 for(int i=0 ; i<psize*J ; i++){
  sum+=rl[i];
 }
 cout<<sum<<endl;
 MPI::Finalize();
}
