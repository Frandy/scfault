#include "poly.h"
#include "cplx.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
using std::string;
using std::cout;
using std::endl;
using std::ios;
using std::fstream;
using std::setw;
using std::setprecision;
using std::setiosflags;

void PolyAdd(vector<double>& n2coef,vector<int>& n2powr,vector<double>& n0coef,vector<int>& n0powr,vector<double>& n1coef,vector<int>& n1powr)
{
	int m = n0coef.size();
	int n = n1coef.size();
	int i = 0, j = 0;

	for(i=0,j=0;i<m && j<n;)
	{
		if(n0powr[i]==n1powr[j])
		{
			n2powr.push_back(n0powr[i]);
			n2coef.push_back(n0coef[i]+n1coef[i]);
			i++;
			j++;
		}
		else if(n0powr[i]<n1powr[j])
		{
			n2powr.push_back(n0powr[i]);
			n2coef.push_back(n0coef[i]);
			i++;
		}
		else
		{
			n2powr.push_back(n1powr[j]);
			n2coef.push_back(n1coef[j]);
			j++;
		}
	}
	if(i==m && j<n)
	{
		for(;j<n;j++)
		{
			n2powr.push_back(n1powr[j]);
			n2coef.push_back(n1coef[j]);
		}
	}
	else if(i<m && j==n)
	{
		for(;i<m;i++)
		{
			n2powr.push_back(n0powr[i]);
			n2coef.push_back(n0coef[i]);
		}
	}
	//return C;
}


void PolyPrint(vector<double>& coef,vector<int>& powr)
{
	unsigned int i = 0;
	cout << "coef: ";
	for(i=0;i<coef.size();i++)
		cout << setw(16) << setprecision(8) << coef[i];
	cout << endl;
	cout << "power:";
	for(i=0;i<powr.size();i++)
		cout << setw(16) << powr[i];
	cout << endl;
}

void PolyAnalysis(vector<double>& numcoef,vector<int>& numpower,vector<double>& dencoef,vector<int>& denpower)
{
	double theta = 0;
//	double fclk = 30e6;	// 30 MHz
	int N = 10000;
	vector<double> freqArray(N,0);
	vector<double> ampArray(N,0);
	vector<double> faiArray(N,0);
	
	int i = 0, j = 0, m = 0, n = 0;
	n = numcoef.size();
	m = dencoef.size();

	if(numpower[m-1]%2==0)
		cout << "true" << endl;

	for(i=0;i<n;i++)
		numpower[i] = numpower[i]/2;
	for(i=0;i<m;i++)
		denpower[i] = denpower[i]/2;

	int maxi = denpower[m-1];
	if(maxi<numpower[n-1])
		maxi = numpower[n-1];
	vector<CPLX> zm(maxi+1);

	CPLX z(0,0);
	CPLX tnum(0,0), tden(0,0);
	CPLX Hz(0,0);
	for(i=0;i<N;i++)
	{
		z = CPLX(cos(theta),sin(theta));
		freqArray[i] = theta; 
		zm[0] = CPLX(1,0);
		for(j=1;j<=maxi;j++)
			zm[j] = zm[j-1] * z;
		tnum = CPLX(0,0);
		for(j=0;j<n;j++)
			tnum += numcoef[j] * zm[numpower[j]];
		tden = CPLX(0,0);
		for(j=0;j<m;j++)
		{
			tden += dencoef[j] * zm[denpower[j]];
		//	cout << "tden:" << setprecision(6) << tden << "\t";
		}
		//cout << endl;
		Hz = tnum / tden;
		//cout << theta << "\t" << z << "\t" << tnum << "\t" << tden << endl;
		ampArray[i] = abs(Hz);
		faiArray[i] = arg(Hz)*180/M_PI;
		theta += 0.00031415926;
	}

	string filename = "res_ac_data.txt";
	fstream file(filename,ios::out);
	for(unsigned int i=0;i<freqArray.size();i++)
	{
		file << setw(12) << setiosflags(ios::scientific) << setprecision(6) << freqArray[i] << "\t" << ampArray[i] << "\t" << faiArray[i] << endl;
	}

}

void PolyAnalysis(vector<double>& numcoef,vector<int>& numpower,vector<double>& dencoef,vector<int>& denpower,vector<double>& freqArray,double clk, fstream& file)
{
	double theta = 0;
//	double fclk = 30e6;	// 30 MHz
	//int N = 100;
	//vector<double> freqArray(N,0);
	int N = freqArray.size();
	//double clk = 100e3;
	//double clk = 100e3;
	//double clk = ckt->Clock();
	vector<double> ampArray(N,0);
	vector<double> faiArray(N,0);
	
//	cout << "poly analysis here, why seg fault" << endl;

	int i = 0, j = 0, m = 0, n = 0;
	n = numcoef.size();
	m = dencoef.size();

	if(numpower[m-1]%2==0)
	{}//	cout << "true" << endl;

	for(i=0;i<n;i++)
		numpower[i] = numpower[i]/2;
	for(i=0;i<m;i++)
		denpower[i] = denpower[i]/2;

	int maxi = denpower[m-1];
	if(maxi<numpower[n-1])
		maxi = numpower[n-1];
	vector<CPLX> zm(maxi+1);

	CPLX z(0,0);
	CPLX tnum(0,0), tden(0,0);
	CPLX Hz(0,0);
	for(i=0;i<N;i++)
	{
		//freqArray[i] = theta; 
		//theta += 0.0314;
		theta = freqArray[i]/clk*2*M_PI;
		z = CPLX(cos(theta),sin(theta));
		zm[0] = CPLX(1,0);
		for(j=1;j<=maxi;j++)
			zm[j] = zm[j-1] * z;
		tnum = CPLX(0,0);
		for(j=0;j<n;j++)
			tnum += numcoef[j] * zm[numpower[j]];
		tden = CPLX(0,0);
		for(j=0;j<m;j++)
			tden += dencoef[j] * zm[denpower[j]];
		Hz = tnum / tden;
		//cout << "tnum:" << tnum << "\ttden:"<< tden << endl;
		ampArray[i] = abs(Hz);
		faiArray[i] = arg(Hz)*180/M_PI;
	}

	//string filename = "res_ac_data.txt";
	//fstream file(filename,ios::out);
	for(unsigned int i=0;i<freqArray.size();i++)
	{
		file << setw(12) << setiosflags(ios::scientific) << setprecision(6) << freqArray[i] << "\t" << ampArray[i] << "\t" << faiArray[i] << endl;
	}

}
/*
void PolyCalc(vector<double>& coef,vector<int>& powr, CPLX& freq)
{
	
}
*/


void PolyAnalysis(vector<double>& numcoef,vector<int>& numpower,vector<double>& dencoef,vector<int>& denpower,vector<double>& freqArray,double clk, vector<CPLX>& res)
{
	double theta = 0;
//	double fclk = 30e6;	// 30 MHz
	//int N = 100;
	//vector<double> freqArray(N,0);
	int N = freqArray.size();

	res = vector<CPLX>(N,CPLX());

	//double clk = 100e3;
	//double clk = 100e3;
	//double clk = ckt->Clock();
	vector<double> ampArray(N,0);
	vector<double> faiArray(N,0);

//	cout << "poly analysis here, why seg fault" << endl;

	int i = 0, j = 0, m = 0, n = 0;
	n = numcoef.size();
	m = dencoef.size();

	if(numpower[m-1]%2==0)
	{}//	cout << "true" << endl;

	for(i=0;i<n;i++)
		numpower[i] = numpower[i]/2;
	for(i=0;i<m;i++)
		denpower[i] = denpower[i]/2;

	int maxi = denpower[m-1];
	if(maxi<numpower[n-1])
		maxi = numpower[n-1];
	vector<CPLX> zm(maxi+1);

	CPLX z(0,0);
	CPLX tnum(0,0), tden(0,0);
	CPLX Hz(0,0);
	for(i=0;i<N;i++)
	{
		//freqArray[i] = theta;
		//theta += 0.0314;
		theta = freqArray[i]/clk*2*M_PI;
		z = CPLX(cos(theta),sin(theta));
		zm[0] = CPLX(1,0);
		for(j=1;j<=maxi;j++)
			zm[j] = zm[j-1] * z;
		tnum = CPLX(0,0);
		for(j=0;j<n;j++)
			tnum += numcoef[j] * zm[numpower[j]];
		tden = CPLX(0,0);
		for(j=0;j<m;j++)
			tden += dencoef[j] * zm[denpower[j]];
		Hz = tnum / tden;
		res[i]=Hz;
		//cout << "tnum:" << tnum << "\ttden:"<< tden << endl;
		//ampArray[i] = abs(Hz);
		//faiArray[i] = arg(Hz)*180/M_PI;
	}

	//string filename = "res_ac_data.txt";
	//fstream file(filename,ios::out);
/*	for(unsigned int i=0;i<freqArray.size();i++)
	{
		file << setw(12) << setiosflags(ios::scientific) << setprecision(6) << freqArray[i] << "\t" << ampArray[i] << "\t" << faiArray[i] << endl;
	}
*/

}
