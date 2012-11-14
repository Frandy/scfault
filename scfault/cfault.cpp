/*
 * cfault.cpp
 *
 *  Created on: Nov 10, 2012
 *      Author: chjd
 */

#include "gpdd.h"

#include <armadillo>
using namespace arma;

#include <iostream>
using std::cout;
using std::endl;

void GPDD::CFaultAnalysis(vector<vector<CPLX> >& resSens,
		vector<vector<CPLX> >& resData, vector<vector<double> >& params)
{
	// data format,
	// resSens,  Hz[0], sens_1[0], sens_2[0]
	// ResData,  mc_0_Hz[0],mc_0_Hz[1]
	// params,   param_0[0], param_0[1]

	cout << "begin c fault analysis" << endl;

	string filename = "cfault.txt";
	ofstream fp(filename.c_str());

	int param_num = params.size();
	int mc_num = params.begin()->size();
	int point_num = resSens.size();

	cout << "mc_num:" << mc_num << endl;
	cout << "param_num:" << param_num << endl;
	cout << "point_num:" << point_num << endl;

	CPLX scalar = CPLX(1e3, 0);

	//	vector<double> scaleup = {100,125,150,175,200};
	vector<CPLX> scaleup =
	{ CPLX(100, 0), CPLX(125, 0), CPLX(150, 0), CPLX(175, 0), CPLX(200, 0) };

#if 0

	//	double scalar = 1e3;//1e3;

	// keep the same.
	Mat<CPLX> A(point_num,param_num);
	Col<CPLX> yx0(point_num);
	//	Mat<double> A(point_num,param_num);
	//	Col<double> yx0(point_num);

	Col<double> x0(param_num); //
	for(int i=0;i<point_num;i++)
	{
		yx0(i) = scalar * resSens[i][0];
		//		yx0(i) = scalar * resSens[i][0].real();
		for(int j=1;j<=param_num;j++)
		{
			//A(i,j-1) = resSens[i][j].real();
			A(i,j-1) = resSens[i][j];
		}
	}
	for(int i=0;i<param_num;i++)
	x0(i) = params[i][0];

	// scale up A, for each col
	for(int i=0;i<param_num;i++)
	{
		for(int j=0;j<point_num;j++)
		A(j,i) = A(j,i) * scaleup[i];
	}

	cout << "A:" << endl;
	cout << A << endl;
	cout << "yx0:" << endl;
	cout << yx0 << endl;
	cout << "x0:" << endl;
	cout << x0 << endl;

	// change with mc
	Col<CPLX> yx(point_num);
	//	Col<double> yx(point_num);
	Col<double> ex(param_num); // exact param, from params
	Col<double> edx(param_num); // ex - x0

	Col<CPLX> dx; // solved dx
	//	Col<double> dx;	// solved dx

	for(int i=0;i<mc_num;i++)
	{
		for(int j=0;j<point_num;j++)
		{
			yx(j) = scalar * resData[i][j];
			//yx(j) = scalar * resData[i][j].real();
		}
		for(int j=0;j<param_num;j++)
		{
			ex(j) = params[j][i];
			edx(j) = ex(j)-x0(j);
		}

		cout << "yx:" << i << endl;
		cout << yx << endl;
		cout << "ex:" << endl;
		cout << ex << endl;
		cout << "yx-yx0:" << endl;
		cout << yx-yx0 << endl;

		dx = solve(A,yx-yx0);

		// scale down dx
		for(int j=0;j<param_num;j++)
		{
			dx(j) = dx(j)*scaleup[j]/scalar;
		}

		cout << "dx:\n" << dx << endl;

		cout << "A . dx - (yx-yx0) = " << endl;
		cout << (A*dx-(yx-yx0)) << endl;
		cout << "A . edx - (yx-yx0) = " << endl;
		cout << (A*edx-(yx-yx0)) << endl;

		// diff dx & edx
		fp << "mc index: " << i << endl;
		fp << "ex:\t";
		for(int j=0;j<param_num;j++)
		{
			fp << ex(j) << "\t";
		}
		fp << endl;
		fp << "edx:\t";
		for(int j=0;j<param_num;j++)
		{
			fp << edx(j) << "\t";
		}
		fp << endl;
		fp << "dx:\t";
		for(int j=0;j<param_num;j++)
		{
			//fp << dx(j).real() << "\t";
			fp << dx(j) << "\t";
		}
		fp << endl << endl;

	}
#else
	Mat<CPLX> sens_Nz(point_num, param_num);
	Mat<CPLX> sens_Dz(point_num, param_num);
	Col<CPLX> Nz(point_num);
	Col<CPLX> Dz(point_num);
	Col<CPLX> Hz(point_num);
	Col<double> ex(param_num);
	Col<double> edx(param_num);
	Col<CPLX> dx(param_num);

	for (int i = 0; i < point_num; i++)
	{
		Nz(i) = resSens[i][0];
		Dz(i) = resSens[i][1];
		for (int j = 1; j <= param_num; j++)
		{
			sens_Nz(i, j - 1) = resSens[i][2 * j];
			sens_Dz(i, j - 1) = resSens[i][2 * j + 1];
		}
	}

	fp << "Nz, Dz, & sens" << endl;
	fp << "sens_Nz" << endl;
	fp << sens_Nz << endl;
	fp << "sens_Dz" << endl;
	fp << sens_Dz << endl;

	for (int k = 0; k < mc_num; k++)
	{
		for (int i = 0; i < point_num; i++)
		{
			Hz(i) = resData[k][i];
		}
		for (int j = 0; j < param_num; j++)
		{
			ex(j) = params[j][k];
			edx(j) = ex(j) - params[j][0];
		}

		// to construct A, and b
		Mat<CPLX> A(point_num, param_num);
		Col<CPLX> b(point_num);
		for (int i = 0; i < point_num; i++)
		{
			for (int j = 0; j < param_num; j++)
			{
				A(i, j) = sens_Nz(i, j) - Hz(i) * sens_Dz(i, j);
			}
			b(i) = Hz(i) * Dz(i) - Nz(i);
		}

		// scale up A, for each col
		for(int i=0;i<param_num;i++)
		{
			for(int j=0;j<point_num;j++)
			{
				A(j,i) = A(j,i) * scaleup[i];
			}
		}

		for(int i=0;i<point_num;i++)
		{
			b(i) = b(i) * scalar;
		}

		dx = solve(A, b);

		cout << "dx:\n" << dx << endl;

		cout << "A . dx - b = " << endl;
		cout << (A * dx - b) << endl;
		cout << "A . edx - b = " << endl;
		cout << (A * edx - b) << endl;

		for(int i=0;i<param_num;i++)
		{
			dx(i) = dx(i) * scaleup[i] / scalar ;
		}


		// diff dx & edx
		fp << "mc index: " << k << endl;
		fp << "ex:\t";
		for (int j = 0; j < param_num; j++)
		{
			fp << ex(j) << "\t";
		}
		fp << endl;
		fp << "edx:\t";
		for (int j = 0; j < param_num; j++)
		{
			fp << edx(j) << "\t";
		}
		fp << endl;
		fp << "dx:\t";
		for (int j = 0; j < param_num; j++)
		{
			//fp << dx(j).real() << "\t";
			fp << dx(j) << "\t";
		}
		fp << endl << endl;

	}
#endif

}

