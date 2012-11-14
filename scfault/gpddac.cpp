#include <fstream>
#include <iomanip>
using std::fstream;
using std::ios;
using std::setw;
using std::setprecision;
using std::setiosflags;
using std::endl;

#include <iostream>
using std::cout;

#include "gpdd.h"
#include "poly.h"

extern GpddNode* pGpddNodeZero;
extern GpddNode* pGpddNodeOne;


bool curValueMark = false;

CPLX GPDD::EvaluateNode(GpddNode* node)
{
//cout << "to evaluate node: " << node->GetSymbol()->Name();
	if(node->Marked()==curValueMark)
	{
//	cout << "\treturn value:" << node->GetValue() << endl;	
		return node->GetValue();
	}
	GpddNode* left = node->GetLeft();
	GpddNode* right = node->GetRight();
	CPLX value = node->GetSymbol()->GetCplxValue();
/*	if(left->Marked()!=curValueMark)
		EvaluateNode(left);
	if(right->Marked()!=curValueMark);
		EvaluateNode(right);
*/
	value *= CPLX(node->GetSignL(),0) * EvaluateNode(left);
	value += CPLX(node->GetSignR(),0) * EvaluateNode(right);
	node->SetValue(value);
	node->Mark(curValueMark);
//	cout << "\treturn value:" << node->GetValue() << endl;	
	return value;
}


CPLX GPDD::Evaluate()
{
	CPLX num(0,0), den(0,0);
	int sign = 1;
	curValueMark = !root->Marked();

	pGpddNodeZero->Mark(curValueMark);
	pGpddNodeOne->Mark(curValueMark);

	num = root->GetLeft()->Value(curValueMark);
	den = root->GetRight()->Value(curValueMark);
//	num = EvaluateNode(root->GetLeft());
//	den = EvaluateNode(root->GetRight());

	root->Mark(curValueMark);
	sign = (-1) * (root->GetSignL()) * (root->GetSignR());
	return CPLX(sign,0)*num/den;
}


void GPDD::ACAnalysis()
{
	vector<double> freqArray;
	if(ckt->GetACTask()==NULL)
		return;
	ckt->GetACTask()->GetF(freqArray);
	CPLX Hs(0,0);
	double amp = 0.0, fai = 0.0;
	vector<double> ampArray(freqArray.size(),0);
	vector<double> faiArray(freqArray.size(),0);
	for(unsigned int i=0;i<freqArray.size();i++)
	{
		ckt->SetupSymbolFreqValue(freqArray.at(i));
		Hs = this->Evaluate();
		amp = abs(Hs);
		fai = arg(Hs)*180/M_PI;
		ampArray[i] = amp;
		faiArray[i] = fai;
	}

	string filename = ckt->FileName();
	int pos = filename.find(".");
	if(pos!=filename.npos)
		filename.replace(pos,4,"_ac_data.txt");
	else
		filename = "res_ac_data.txt";

	fstream file(filename,ios::out);
	for(unsigned int i=0;i<freqArray.size();i++)
	{
		file << setw(12) << setiosflags(ios::scientific) << setprecision(6) << freqArray[i] << "\t" << ampArray[i] << "\t" << faiArray[i] << endl;
	}
}

void GPDD::ACAnalysisWithSCCoef(string filename)
{
	// coef,
	// calculate
	cout << "ac analysis with coef" << endl;
	vector<double> freqArray;
	if(ckt->GetACTask()==NULL)
		return;
	ckt->GetACTask()->GetF(freqArray);
	//PrintCoef();
	if(ckt->Infinity())
		EvaluateInfinityCoef();
	else
		EvaluateCoef();
	cout << "coef done" << endl;
	fstream file(filename.c_str(),ios::out);
	double clk = ckt->Clock();
	PolyAnalysis(numcoef3,numpower3,dencoef,denpower,freqArray,clk,file);
	//PolyAnalysis(numcoef3,numpower3,dencoef,denpower);
	file.close();
}

void GPDD::MonteAnalysis(string filename)
{
	cout << "begin monte" << endl;
	if(ckt->paramList.paramList.empty())
		return;
/*	if(ckt->paramList.paramList.size()>1)
	{
		cout << "warning: more than one parameters" << endl;
		return;
	}
	vector<double> freqArray;
	if(ckt->GetACTask()==NULL)
		return;
	ckt->GetACTask()->GetF(freqArray);
	fstream res(filename.c_str(),ios::out);
	list<ParamNode*>::iterator it = ckt->paramList.paramList.begin();
	for(;it!=ckt->paramList.paramList.end();it++)
	{
		ParamNode* param = (*it);
		param->ReadData();
		//cout << "process first param," << param->param << endl;
		for(int i=0;i<param->paramdata.size();i++)
		{
			double value = param->paramdata[i]; 
			cout << "value of param: " << value << endl;
			//res << "index = " << i+1 << "\t" << param->param << " = "<< value << endl;
			param->UpdateSymbValue(value);
			EvaluateCoef();
			PolyAnalysis(numcoef3,numpower3,dencoef,denpower,freqArray,res);					
			res << endl;
		}
	}
	res.close();	
*/

	vector<double> freqArray;
	if(ckt->GetACTask()==NULL)
		return;
	ckt->GetACTask()->GetF(freqArray);
	fstream res(filename.c_str(),ios::out);
	list<ParamNode*>::iterator it = ckt->paramList.paramList.begin();
	// readin all param values
	for(;it!=ckt->paramList.paramList.end();it++)
	{
		ParamNode* param = (*it);
		param->ReadData();
	}
	it = ckt->paramList.paramList.begin();
	int mc_num = (*it)->paramdata.size();
	
	double clk = ckt->Clock();

	for(int i=0;i<mc_num;i++)
	{
		//cout << "index:" << i << endl;
		// update all param symbols' values
		it = ckt->paramList.paramList.begin();
		for(;it!=ckt->paramList.paramList.end();it++)
		{
			ParamNode* param = (*it);
			double value = param->paramdata[i]; 
			//cout << param->param << "=" << value << "\t";
			param->UpdateSymbValue(value);
		}
		// print all symbol value
		//ckt->Print(cout);
		//cout << endl;
		// one mc result
		EvaluateCoef();
		PolyAnalysis(numcoef3,numpower3,dencoef,denpower,freqArray,clk,res);					
		res << endl;
	}
	res.close();
}

// freq sens_mag sens_phase
void GPDD::SensAnalysis(string filename)
{
	cout << "***********begin sens*****************" << endl;
	vector<double> freqArray;
	if(ckt->GetACTask()==NULL)
		return;
	ckt->GetACTask()->GetF(freqArray);
	// readin all param values
	ckt->paramList.ReadData();
	ckt->paramList.Sort();
	ckt->paramList.Print();
	// evaluate ac coef
	list<ParamNode*>::iterator it = ckt->paramList.paramList.begin();
	for(int i=0;it!=ckt->paramList.paramList.end();it++)
	{
		ParamNode* param = (*it);
		double value = param->paramdata[i]; 
		cout << param->param << "=" << value << "\t";
		param->UpdateSymbValue(value);
	}
	EvaluateCoef();
	fstream res(filename.c_str(),ios::out);
	// evaluate sens coef
	cout << "*****begin evaluate sens coef*******" << endl;	
	it = ckt->paramList.paramList.begin();
	for(;it!=ckt->paramList.paramList.end();it++)
	{
		ParamNode* param = (*it);
		param->Print();
		cout << "sens param:" << param->param << endl;
		param->sens_num_coef = new vector<double>(numcoef3.size(),0);
//		param->Print();
		param->sens_den_coef = new vector<double>(dencoef.size(),0);
		vector<double> tmp_num_coef;
		vector<double> tmp_den_coef;
		list<Symbol*>::iterator sit = param->paramSymbList.begin();
//		cout << "here" << endl;
		for(;sit!=param->paramSymbList.end();sit++)
		{
//			cout << "here" << endl;
			cout << (*sit) << endl;
			cout << "to sens symbol:" << (*sit)->Name() <<  endl;
			tmp_num_coef.clear();
			tmp_den_coef.clear();
			EvaluateCoefSens((*sit),tmp_num_coef,tmp_den_coef);
			if((*sit)->Name()[0]=='L')
			{
				for(int j=0;j<param->sens_num_coef->size();j++)
				{
					(*param->sens_num_coef)[j] -= tmp_num_coef[j];
					(*param->sens_den_coef)[j] -= tmp_den_coef[j];
				}
			}
			else if((*sit)->Name()[0]=='R')
			{
				for(int j=0;j<param->sens_num_coef->size();j++)
				{
					(*param->sens_num_coef)[j] += tmp_num_coef[j];
					(*param->sens_den_coef)[j] += tmp_den_coef[j];
				}
			
			}
		}
		cout << "final sens for param:" << param->param << endl;
		cout << "num" << endl;
		PolyPrint(*param->sens_num_coef,numpower3);
		cout << "den:" << endl;
		PolyPrint(*param->sens_den_coef,denpower);

	}
	// sens coef done	
	// evaluate ac & sens
	double theta = 0;
	int N = freqArray.size();
	//double clk = 1e5;
	double clk = ckt->Clock();

	int i = 0, j = 0;
	int m = 0, n = 0;
	n = numcoef.size();
	m = dencoef.size();

	if(numpower[m-1]%2==0)
		cout << "true" << endl;

	for(i=0;i<n;i++)
		numpower[i] = numpower[i]/2;
	for(i=0;i<m;i++)
		denpower[i] = denpower[i]/2;

	int maxi = denpower[m];
	if(maxi<numpower[n])
		maxi = numpower[n];
	vector<CPLX> zm(maxi+1);

	CPLX z(0,0);
	CPLX tnum(0,0), tden(0,0);
	CPLX sens_tnum(0,0), sens_tden(0,0);
	CPLX Hz(0,0),sens;
	vector<double> linedata;
	double mag, phi, mag_sens, phi_sens;
	double bound_mag_max,bound_mag_min,bound_phi_max,bound_phi_min;
	double delta_mag, delta_phi;
	list<ParamNode*>::iterator pit = ckt->paramList.paramList.begin();
	for(i=0;i<N;i++)
	{
		linedata.clear();
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
		mag = abs(Hz);
		phi = arg(Hz);//*180/M_PI;
		linedata.push_back(freqArray[i]);
		linedata.push_back(mag);
		linedata.push_back(phi*180/M_PI);
		// sens
		// bound
		bound_mag_max = mag;
		bound_mag_min = mag;
		bound_phi_max = phi;
		bound_phi_min = phi;

		//
		pit = ckt->paramList.paramList.begin();
		for(;pit!=ckt->paramList.paramList.end();pit++)
		{
			sens_tnum = CPLX(0,0);
			for(j=0;j<(*pit)->sens_num_coef->size();j++)
				sens_tnum += (*(*pit)->sens_num_coef)[j] * zm[numpower[j]];
			sens_tden = CPLX(0,0);
			for(j=0;j<(*pit)->sens_den_coef->size();j++)
				sens_tden += (*(*pit)->sens_den_coef)[j] * zm[denpower[j]];
			sens = CPLX((*pit)->paramdata[0],0)/tnum*sens_tnum - CPLX((*pit)->paramdata[0],0)/tden*sens_tden; 
			mag_sens = sens.real();
			phi_sens = sens.imag()/arg(Hz);
			linedata.push_back(mag_sens);
			linedata.push_back(phi_sens*180/M_PI);
			delta_mag = abs(mag_sens*mag/(*pit)->paramdata[0]*(*pit)->paramdata[1]);
			bound_mag_max += delta_mag;
			bound_mag_min -= delta_mag;
			//delta_phi = abs(phi_sens*phi/(*pit)->paramdata[0]*(*pit)->paramdata[1]);
			delta_phi = abs(sens.imag()/(*pit)->paramdata[0]*(*pit)->paramdata[1]);
			bound_phi_max += delta_phi;
			bound_phi_min -= delta_phi;
			//cout << (*pit)->param << "\tdelta_phi:" << delta_phi << "\tmax:" << bound_phi_max << "\tmin:" << bound_phi_min << endl; 
		}
		
		if(bound_mag_max<0)
			bound_mag_max=1e-8;
		if(bound_mag_min<0)
			bound_mag_min=1e-8;
		
		linedata.push_back(bound_mag_max);
		linedata.push_back(bound_mag_min);
		linedata.push_back(bound_phi_max*180/M_PI);
		linedata.push_back(bound_phi_min*180/M_PI);

		for(j=0;j<linedata.size();j++)
			res << setw(14) << setiosflags(ios::scientific) << setprecision(8) << linedata[j] << "\t";
		res << endl;
	}
}

void GPDD::MonteFaultAnalysis(vector<vector<CPLX> >& res,vector<vector<double> >& params)
{
	cout << "begin monte" << endl;
	if(ckt->paramList.paramList.empty())
		return;

	vector<double> freqArray;
	if(ckt->GetACTask()==NULL)
		return;
	ckt->GetACTask()->GetF(freqArray);
//	fstream res(filename.c_str(),ios::out);
	list<ParamNode*>::iterator it = ckt->paramList.paramList.begin();
	//params = vector<vector<double> >(ckt->paramList.paramList.size());
	// readin all param values
	for(;it!=ckt->paramList.paramList.end();it++)
	{
		ParamNode* param = (*it);
		(*it)->paramdata.clear();
		param->ReadData();
		params.push_back((*it)->paramdata);
	}
	it = ckt->paramList.paramList.begin();
	int mc_num = (*it)->paramdata.size();



	double clk = ckt->Clock();

	for(int i=0;i<mc_num;i++)
	{
		//cout << "index:" << i << endl;
		// update all param symbols' values
		it = ckt->paramList.paramList.begin();
		for(;it!=ckt->paramList.paramList.end();it++)
		{
			ParamNode* param = (*it);
			double value = param->paramdata[i];
			//cout << param->param << "=" << value << "\t";
			param->UpdateSymbValue(value);
		}
		// print all symbol value
		//ckt->Print(cout);
		//cout << endl;
		// one mc result
		EvaluateCoef();
		vector<CPLX> resData;
		PolyAnalysis(numcoef3,numpower3,dencoef,denpower,freqArray,clk,resData);
		//res << endl;
		res.push_back(resData);

	}
	//res.close();
}


void GPDD::SensParametricFault(vector<double>& freqArray,vector<vector<CPLX> >& res)
{
	cout << "***********begin sens*****************" << endl;
		//vector<double> freqArray;
		if(ckt->GetACTask()==NULL)
			return;
		ckt->GetACTask()->GetF(freqArray);
		// readin all param values
		ckt->paramList.ReadData();
		ckt->paramList.Sort();
		ckt->paramList.Print();
		// evaluate ac coef
		list<ParamNode*>::iterator it = ckt->paramList.paramList.begin();
		for(int i=0;it!=ckt->paramList.paramList.end();it++)
		{
			ParamNode* param = (*it);
			double value = param->paramdata[i];
			cout << param->param << "=" << value << "\t";
			param->UpdateSymbValue(value);
		}
		EvaluateCoef();
		//fstream res(filename.c_str(),ios::out);
		// evaluate sens coef
		cout << "*****begin evaluate sens coef*******" << endl;
		it = ckt->paramList.paramList.begin();
		for(;it!=ckt->paramList.paramList.end();it++)
		{
			ParamNode* param = (*it);
			param->Print();
			cout << "sens param:" << param->param << endl;
			param->sens_num_coef = new vector<double>(numcoef3.size(),0);
	//		param->Print();
			param->sens_den_coef = new vector<double>(dencoef.size(),0);
			vector<double> tmp_num_coef;
			vector<double> tmp_den_coef;
			list<Symbol*>::iterator sit = param->paramSymbList.begin();
	//		cout << "here" << endl;
			for(;sit!=param->paramSymbList.end();sit++)
			{
	//			cout << "here" << endl;
				cout << (*sit) << endl;
				cout << "to sens symbol:" << (*sit)->Name() <<  endl;
				tmp_num_coef.clear();
				tmp_den_coef.clear();
				EvaluateCoefSens((*sit),tmp_num_coef,tmp_den_coef);
				if((*sit)->Name()[0]=='L')
				{
					for(int j=0;j<param->sens_num_coef->size();j++)
					{
						(*param->sens_num_coef)[j] -= tmp_num_coef[j];
						(*param->sens_den_coef)[j] -= tmp_den_coef[j];
					}
				}
				else if((*sit)->Name()[0]=='R')
				{
					for(int j=0;j<param->sens_num_coef->size();j++)
					{
						(*param->sens_num_coef)[j] += tmp_num_coef[j];
						(*param->sens_den_coef)[j] += tmp_den_coef[j];
					}

				}
			}
			cout << "final sens for param:" << param->param << endl;
			cout << "num" << endl;
			PolyPrint(*param->sens_num_coef,numpower3);
			cout << "den:" << endl;
			PolyPrint(*param->sens_den_coef,denpower);

		}
		// sens coef done
		// evaluate ac & sens
		double theta = 0;
		int N = freqArray.size();
		//double clk = 1e5;
		double clk = ckt->Clock();

		int i = 0, j = 0;
		int m = 0, n = 0;
		n = numcoef.size();
		m = dencoef.size();

		cout << "for ever" << endl;
		cout << n << endl;

		if(numpower[m-1]%2==0)
			cout << "true" << endl;



		for(i=0;i<n;i++)
			numpower[i] = numpower[i]/2;
		for(i=0;i<m;i++)
			denpower[i] = denpower[i]/2;

		cout << "for ever" << endl;

		int maxi = denpower[m];
		if(maxi<numpower[n])
			maxi = numpower[n];
		vector<CPLX> zm(maxi+1);

		cout << "begin TF & sens evaluation" << endl;

		CPLX z(0,0);
		CPLX tnum(0,0), tden(0,0);
		CPLX sens_tnum(0,0), sens_tden(0,0);
		CPLX Hz(0,0),sens;
		vector<CPLX> linedata;
//		double mag, phi, mag_sens, phi_sens;
//		double bound_mag_max,bound_mag_min,bound_phi_max,bound_phi_min;
//		double delta_mag, delta_phi;
		list<ParamNode*>::iterator pit = ckt->paramList.paramList.begin();
		for(i=0;i<N;i++)
		{
			linedata.clear();
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
//			mag = abs(Hz);
//			phi = arg(Hz);//*180/M_PI;

		// if use Hz, and sens
		//	linedata.push_back(Hz);
		// else, use Nz, Dz, Sens_Nz, Sens_Dz
			linedata.push_back(tnum);
			linedata.push_back(tden);
			// sens

			//
			pit = ckt->paramList.paramList.begin();
			for(;pit!=ckt->paramList.paramList.end();pit++)
			{
				sens_tnum = CPLX(0,0);
				for(j=0;j<(*pit)->sens_num_coef->size();j++)
					sens_tnum += (*(*pit)->sens_num_coef)[j] * zm[numpower[j]];
				sens_tden = CPLX(0,0);
				for(j=0;j<(*pit)->sens_den_coef->size();j++)
					sens_tden += (*(*pit)->sens_den_coef)[j] * zm[denpower[j]];
	//			sens = CPLX((*pit)->paramdata[0],0)/tnum*sens_tnum - CPLX((*pit)->paramdata[0],0)/tden*sens_tden;
				sens = (sens_tnum*tden-tnum*sens_tden)/(tden*tden);
				// in fact, it should be derivatives.
			//	linedata.push_back(sens);
				linedata.push_back(sens_tnum);
				linedata.push_back(sens_tden);
			}

			res.push_back(linedata);
		}
}

