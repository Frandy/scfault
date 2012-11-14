#include <iostream>
#include <time.h>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;

#include "gpdd.h"
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
	if(argc!=2)
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

	myckt->Print(cout);
	
	clock_t t0 = clock();
/* - - - - - - - - - - - - - - - - - - - - - - - - - - */
	cerr << "to test GPDD..." << endl;
	GPDD mygpdd(myckt);
	mygpdd.InitRoot();
	//cout << "--GPDD Root Init Done!" << endl;
	//mygpdd.Print(cout);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - */
	cerr << "--Begin GraphReduction--" << endl;
#ifdef GraphReduction_BFS
	mygpdd.GraphReductionBFS();
#elif  GraphReduction_DFS
//	mygpdd.GraphReductionDFS();
#endif
	cerr << "\t--GraphReduction Done!!!" << endl;
	clock_t t1 = clock();
	cerr << "time: " << (double(t1-t0)/CLOCKS_PER_SEC) << " seconds"<< endl;
#ifdef PRINT_EXP
//	mygpdd.PrintExp(cout);
#endif

/* - - - - - - - - - - - - - - - - - - - - - - - - - - */
//  test ZS
	cerr << "--test ZS..." << endl;
#ifdef ZERO_SUPPRESS_DIRECT
//	mygpdd.ZeroSuppress();
#else /* ZERO_SUPPRESS_RECURSIVE */
	mygpdd.ZeroSuppressRecursive();
//	mygpdd.ZeroSuppressInList();
#endif
	cerr << "\t--ZS done!!!" << endl;
	clock_t t2 = clock();
	cerr << "time: " << (double(t2-t1)/CLOCKS_PER_SEC) << " seconds"<< endl;
#ifdef PRINT_EXP	
//	mygpdd.PrintExp(cout);
#endif

/* - - - - - - - - - - - - - - - - - - - - - - - - - - */
// test reduce
	cerr << "--test Reduce..." << endl;
	mygpdd.ReduceR();
//	mygpdd.Reduce();
	cerr << "\t--Reduce Done!!!" << endl;
	clock_t t3 = clock();
	cerr << "time: " << (double(t3-t2)/CLOCKS_PER_SEC) << " seconds"<< endl;
#ifdef PRINT_EXP	
	mygpdd.PrintExp(cout);
	mygpdd.PrintTerm();
#endif

#ifdef PRINT_COEF
	mygpdd.SExpand();
	mygpdd.PrintCoef();
#endif


/* - - - - - - - - - - - - - - - - - - - - - - - - - - */
//	test garbage collect
	cerr << "--garbage collenting..." << endl;
	mygpdd.GarbageCollect();
	cerr << "\t--garbage collection done!!!" << endl;
	clock_t t4 = clock();
	cerr << "time: " << (double(t4-t3)/CLOCKS_PER_SEC) << " seconds"<< endl;

/* - - - - - - - - - - - - - - - - - - - - - - - - - - */
	cerr << "test AC analysis..." << endl;
	mygpdd.ACCoefAnalysis();
	//	mygpdd.ACAnalysis();
	cerr << "--\tAC done!!!" << endl;
	clock_t t5 = clock();
	cerr << "time: " << (double(t5-t4)/CLOCKS_PER_SEC) << " seconds"<< endl;

#ifdef DEBUG_SIGN
//	mygpdd.PrintNode();
#endif

	return 0;
}

