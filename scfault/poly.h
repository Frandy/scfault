#ifndef POLY_H_
#define POLY_H_

#include <vector>
#include <fstream>
using std::vector;
using std::fstream;

#include "cplx.h"

void PolyAdd(vector<double>& n2coef,vector<int>& n2powr,vector<double>& n0coef,vector<int>& n0powr,vector<double>& n1coef,vector<int>& n1powr);

void PolyPrint(vector<double>& coef,vector<int>& powr);

//void PolyCalc(vector<double>& coef,vector<int>& powr,CPLX& freq);

void PolyAnalysis(vector<double>& numcoef,vector<int>& numpower,vector<double>& dencoef,vector<int>& denpower);

void PolyAnalysis(vector<double>& numcoef,vector<int>& numpower,vector<double>& dencoef,vector<int>& denpower,vector<double>& freqArray,double clk,fstream& file);

void PolyAnalysis(vector<double>& numcoef,vector<int>& numpower,vector<double>& dencoef,vector<int>& denpower,vector<double>& freqArray,double clk, vector<CPLX>& res);

#endif
