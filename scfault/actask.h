#ifndef ACTASK_H
#define ACTASK_H

#include <vector>
using std::vector;

class ACTask{
public:
	ACTask(int tp,int no,double st,double ef){
		type = tp;
		num = no;
		start = st;
		endf = ef;
	}
	void GetF(vector<double>& farray);
private:
	ACTask();
	int type; // dec or lin
	int num; // num or step;
	double start;
	double endf;
};

#endif
