#pragma once
#include "luafc.h"

void Allocate2doub(double ***A, int rowsize, int colsize);
void illHilbert(double ***A, int Ns, int Nc, int startr);
void Deallocate2doub(double ***A, int rowsize);
void OutputMat(double **A, int rowsize, int colsize);
void BinomMat(double ***A, int Ns, int Nc, int startc);
void MultiMat(double ***C, double **A, double **B, int xsize, int ysize);
double binomcoef(int n, int k);
double curcoef(int n, int k);
long factorial(int n);
