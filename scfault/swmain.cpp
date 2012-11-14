#include <iostream>
#include <time.h>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;

#include "gpdd.h"
#include "poly.h"
#include "parserdefs.h"
#include "parserbison.hpp"
#include "option.h"

CKT* myckt;
Symbol* symbolX;

long int GpddNode::total = 0;
int Graph::graphSharedCnt = 0;

int main(int argc,char* argv[])
{
	string filename;
	if(argc<2)
	{
		cout << "usage: ./gpdd filename" << endl;
		cout << "please input circuit file: ";
		cin >> filename;
	}
	else 
	{
		filename = argv[1];
	}

	myparser(filename.c_str());
	myckt->PostProcessCSC();
//	myckt->Print(cout);

	clock_t t0 = clock();
/* - - - - - - - - - - - - - - - - - - - - - - - - - - */
	cerr << "to test GPDD..." << endl;
	GPDD mygpdd(myckt);
	mygpdd.InitRoot();	

	mygpdd.GraphReductionBFS();

//	mygpdd.PrintExp(cout);

cout << "reduction done" << endl;	
	mygpdd.ZeroSuppressRecursive();
cout << "zero done" << endl;	
	mygpdd.ReduceR();
cout << "reduce done" << endl;	
	mygpdd.GarbageCollect();

//	mygpdd.PrintExp(cout);
#ifdef PRINT_EXP	
#endif
	mygpdd.PrintTerm();

#ifdef PRINT_COEF
/*	if(myckt->Infinity())
		mygpdd.InfinityExpand();
	mygpdd.SExpand();
*/
	mygpdd.SExpand();
//	if(myckt->Infinity())
//		mygpdd.EvaluateInfinityCoef();
	mygpdd.PrintCoef();
#endif
	
	clock_t t1 = clock();

	if(argc<3)
		mygpdd.ACAnalysisWithSCCoef("res_ac_data.txt");
	else if(string(argv[2])=="mc")
		mygpdd.MonteAnalysis("mc_6m.txt");
	else if(string(argv[2])=="sens")
		mygpdd.SensAnalysis("sens.txt");	
	else if(string(argv[2])=="fault")
	{
		vector<double> freqArray;
		vector<vector<CPLX> > resSens;
		vector<vector<CPLX> > resData;
		vector<vector<double> > params;
		mygpdd.SensParametricFault(freqArray,resSens);
		mygpdd.MonteFaultAnalysis(resData,params);
		mygpdd.CFaultAnalysis(resSens,resData,params);
	}

	clock_t t2 = clock();

/* - - - - - - - - - - - - - - - - - - - - - - - - - - */
	//mygpdd.ACCoefAnalysis();
	//	mygpdd.ACAnalysis();

#ifdef DEBUG_SIGN
//	mygpdd.PrintNode();
#endif

	cerr << "Time Statistics:" << endl;
	cerr <<"Building GPDD:\t" << (double(t1-t0)/CLOCKS_PER_SEC) << "s" << endl;
	cerr <<"AC Analysis:\t" << (double(t2-t1)/CLOCKS_PER_SEC) << "s" << endl;

	return 0;
}

