#include <cmath>
#include <iostream>
using std::cout;
using std::endl;

#include "actask.h"


void ACTask::GetF(vector<double>& farray){
	if(type==0){
	// lin
		int N = num; // total points
		farray = vector<double>(N);
		int i = 0;
		double step = (endf-start)/(num-1);
		farray[0] = start;
		for(i=1;i<N;i++){
			farray[i] = farray[i-1] + step;
		}
	}
	else if(type==1){
	// dec
		double logstart = log10(start);
		double logstep = 1.0/num;
	//	double step = pow(10,logstep);
		double logendf = log10(endf);
		int N = (int)((logendf-logstart)*num+0.5)+1;
/*		cout << "start:" << start << "  log:" << logstart << endl;
		cout << "endf: " << endf << "   log:" << logendf << endl;
		cout << "step:"  << step << "   log:" << logstep << endl;
*/		farray = vector<double>(N);
		int i = 0;
		farray[0] = start;
cout << start << endl;		
		double tmp = logstart;
		for(i=1;i<N;i++){
			tmp = tmp + logstep;
			farray[i] = pow(10,tmp);
			//farray[i] = farray[i-1] * step;
		}
	}
}
