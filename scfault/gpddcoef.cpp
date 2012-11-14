#include "coefnode.h"
#include "gpddnode.h"
#include "gpdd.h"
#include "poly.h"
#include <fstream>
#include <iomanip>
using std::ios;
using std::fstream;
using std::setw;
using std::setprecision;
using std::setiosflags;

CoefNode* pCoefOne;
CoefNode* pCoefZero;

extern GpddNode* pGpddNodeOne;
extern GpddNode* pGpddNodeZero;

void GPDD::CreateCoefInit()
{
	pCoefOne = new CoefNode();
	pCoefOne->spower.push_back(0);
	pCoefOne->scoef.push_back(pGpddNodeOne);
	pGpddNodeOne->SetCoef(pCoefOne);

	pCoefZero = new CoefNode();
	pCoefZero->spower.push_back(0);
	pCoefZero->scoef.push_back(pGpddNodeZero);
	pGpddNodeZero->SetCoef(pCoefZero);
}

void GPDD::SExpand()
{
	cout << "to do sexpand..." << endl;
	bool flag = root->GetLeft()->Marked();
	flag = !flag;
	CreateCoefInit();
	pGpddNodeOne->Mark(flag);
	pGpddNodeZero->Mark(flag);
	root->Mark(flag);
	SExpandNode(root->GetLeft(),flag);
	SExpandNode(root->GetRight(),flag);

	root2->Mark(flag);
	SExpandNode(root2->GetLeft(),flag);
	SExpandNode(root2->GetRight(),flag);
	cout << "sexpand done." << endl;
}

void CoefMultAdd(CoefNode* cn, GpddNode* p, int index)
{
	int i = 0, j = 0, m = 0, n = 0;
	CoefNode* cleft = p->GetLeft()->GetCoef();
	CoefNode* cright = p->GetRight()->GetCoef();
	m = cleft->scoef.size();
	n = cright->scoef.size();
	
	for(i=0,j=0;i<m && j<n;)
	{
		if(cleft->spower[i]+index==cright->spower[j])
		{
			GpddNode* pn = new GpddNode(p->GetSymbol());
			pn->SetLeft(cleft->scoef[i]);
			pn->SetRight(cright->scoef[j]);
			pn->SetSignL(p->GetSignL());
			pn->SetSignR(p->GetSignR());
			cn->scoef.push_back(pn);
			cn->spower.push_back(cright->spower[j]);
			i++;
			j++;
		}
		else if(cleft->spower[i]+index<cright->spower[j])
		{
			GpddNode* pn = new GpddNode(p->GetSymbol());
			pn->SetLeft(cleft->scoef[i]);
			pn->SetRight(pGpddNodeZero);
			pn->SetSignL(p->GetSignL());
			pn->SetSignR(p->GetSignR());
			cn->scoef.push_back(pn);
			cn->spower.push_back(cleft->spower[i]+index);
			i++;
		}
		else
		{
			cn->scoef.push_back(cright->scoef[j]);
			cn->spower.push_back(cright->spower[j]);
			j++;
		}
	}
	if(i==m && j<n)
	{
		for(;j<n;j++)
		{
			cn->scoef.push_back(cright->scoef[j]);
			cn->spower.push_back(cright->spower[j]);
		}
	}
	else if(i<m && j==n)
	{
		for(;i<m;i++)
		{
			GpddNode* pn = new GpddNode(p->GetSymbol());
			pn->SetLeft(cleft->scoef[i]);
			pn->SetRight(pGpddNodeZero);
			pn->SetSignL(p->GetSignL());
			pn->SetSignR(p->GetSignR());
			cn->scoef.push_back(pn);
			cn->spower.push_back(cleft->spower[i]+index);	
		}
	}

}

void GPDD::SExpandNode(GpddNode* p, bool flag)
{
	if(p->Marked()==flag)
		return;
	if(p->GetLeft()->Marked()!=flag)
		SExpandNode(p->GetLeft(),flag);
	if(p->GetRight()->Marked()!=flag)
		SExpandNode(p->GetRight(),flag);

/*	cout << "\t left coef:" << endl;
	PrintNodeCoef(p->GetLeft());
	cout << "\t right coef:" << endl;
	PrintNodeCoef(p->GetRight());
*/
	CoefNode* cn = new CoefNode();

	if(p->GetSymbol()->Type()==L)
	{
		CoefMultAdd(cn,p,-1);
	}
	else if(p->GetSymbol()->Type()==C)
	{
		CoefMultAdd(cn,p,1);
	}
	else
	{
		CoefMultAdd(cn,p,0);
	}
	p->SetCoef(cn);
//		cout << "node:" << p->GetSymbol()->Name() << endl;
//		PrintNodeCoef(p);

	p->Mark(flag);
}


void GPDD::InfinityExpand()
{
	cout << "to do infinity expand..." << endl;
	bool flag = root->GetLeft()->Marked();
	flag = !flag;
	CreateCoefInit();
	pGpddNodeOne->Mark(flag);
	pGpddNodeZero->Mark(flag);
	root->Mark(flag);
	InfinityExpandNode(root->GetLeft(),flag);
	
	//cout << "root left infinity done" << endl;

	InfinityExpandNode(root->GetRight(),flag);

	//cout << "root right infinity done" << endl;

	CoefNode* cn0 = root->GetLeft()->GetCoef();
	CoefNode* cm0 = root->GetRight()->GetCoef();
	
	if(cn0==NULL)
		cn0 = pGpddNodeZero->GetCoef();

	if(cm0==NULL)
		cm0 = pGpddNodeZero->GetCoef();

	root2->Mark(flag);
	InfinityExpandNode(root2->GetLeft(),flag);
	
	//cout << "root_2 left infinity done" << endl;

	InfinityExpandNode(root2->GetRight(),flag);

	//cout << "root_2 right infinity done" << endl;

	CoefNode* cn = root2->GetLeft()->GetCoef();
	CoefNode* cm = root2->GetRight()->GetCoef();

	if(cn==NULL)
		cn = pGpddNodeZero->GetCoef();
	if(cm==NULL)
		cm = pGpddNodeZero->GetCoef();

	//cout << cn << "\t" << cm << endl;
	//cout << cn->spower.size() << "\t" << cm->spower.size() << endl;
	
	PrintCoef();

	if(cn0->spower[cn0->spower.size()-1]!=cm0->spower[cm0->spower.size()-1])
	{
		cn0 = pGpddNodeZero->GetCoef();
		cm0 = pGpddNodeZero->GetCoef();
	}
	root->SetLeft(cn0->scoef[cn0->scoef.size()-1]);
	root->SetRight(cm0->scoef[cm0->scoef.size()-1]);

	if(cn->spower[cn->spower.size()-1]!=cm->spower[cm->spower.size()-1])
	{
		cn = pGpddNodeZero->GetCoef();
		cm = pGpddNodeZero->GetCoef();
	}
	root2->SetLeft(cn->scoef[cn->scoef.size()-1]);
	root2->SetRight(cm->scoef[cm->scoef.size()-1]);
	cout << "infinity sexpand done." << endl;

}

void GPDD::EvaluateInfinityCoef()
{
	// infinity evaluation after coef s-expand
	numcoef.clear();
	numpower.clear();
	dencoef.clear();
	denpower.clear();
	numcoef2.clear();
	numpower2.clear();
	dencoef2.clear();
	denpower2.clear();
	numcoef3.clear();
	numpower3.clear();	
	int i = 0, n = 0, m = 0;
	int small;
	bool flag;
	int maxInfinityOrder = 0;
//	int maxOrder = 0;

// fisrt cm, then cn0, cn2, since they share the denominator
	CoefNode* cm = root->GetRight()->GetCoef();
	m = cm->scoef.size();
	denpower = cm->spower;

	flag = cm->scoef[0]->Marked();
	flag = !flag;
	pGpddNodeOne->Mark(flag);
	pGpddNodeZero->Mark(flag);

	maxInfinityOrder = 0;
	// find the max infinity order from the denominator
	for(i=0;i<m;i++)
	{	
		EvaluateInfinityCoefNode(cm->scoef[i],flag);
		int torder = cm->scoef[i]->GetInfinityOrder();
		if(torder>maxInfinityOrder)
			maxInfinityOrder = torder;
	}

	for(i=0;i<m;i++)
	{	
		double value = cm->scoef[i]->GetValue().real();
		int torder = cm->scoef[i]->GetInfinityOrder();
		if(torder<maxInfinityOrder)
			value = 0.0;
		dencoef.push_back(value);
//		denpower[i] = (denpower[i]-small);
	}

	small = denpower[0];

root_0:	
	CoefNode* cn = root->GetLeft()->GetCoef();
	n = cn->scoef.size();
	if(n==0)
	{
		cout << "root 0 empty num" << endl;
		goto root_2;
	}
	numpower = cn->spower;
	
	if(numpower[0]<small)
		small = numpower[0];
	
	for(i=0;i<n;i++)
	{	
		EvaluateInfinityCoefNode(cn->scoef[i],flag);
	}
	for(i=0;i<n;i++)
	{	
		double value = cn->scoef[i]->GetValue().real();
		int torder = cn->scoef[i]->GetInfinityOrder();
		if(torder<maxInfinityOrder)
			value = 0.0;
		numcoef.push_back(value);
//		numpower[i] = (numpower[i]-small);
	}
/*
	cout << "small order comp = " << small << endl;
	cout << "num: " << endl;
	PolyPrint(numcoef,numpower);
	cout << "den: " << endl;
	PolyPrint(dencoef,denpower);
*/
root_2:
	cn = root2->GetLeft()->GetCoef();
	if(cn==NULL)
		goto root_3;
	n = cn->scoef.size();
	if(n==0)
	{
		cout << "root 2 empty num" << endl;
		goto root_3;
	}
	numpower2 = cn->spower;
	
	if(numpower2[0]<small)
		small = numpower2[0];

	for(i=0;i<n;i++)
	{	
		EvaluateInfinityCoefNode(cn->scoef[i],flag);
	}
	for(i=0;i<n;i++)
	{	
		double value = cn->scoef[i]->GetValue().real();
		int torder = cn->scoef[i]->GetInfinityOrder();
		if(torder<maxInfinityOrder)
			value = 0.0;
		numcoef2.push_back(value);
//		numpower2[i] = (numpower[i]-small);
	}

root_3:
	if(small<0)
	{
		n = denpower.size();
		for(i=0;i<n;i++)
			denpower[i] = (denpower[i]-small);
		n = numpower.size();
		for(i=0;i<n;i++)
			numpower[i] = numpower[i]-small;
		n = numpower2.size();
		for(i=0;i<n;i++)
			numpower2[i] = numpower2[i]-small;
	}

	int scOutStat = ckt->GetScOutStat();
	i = 0;
	if(scOutStat==0 || scOutStat==2)
	{
		for(i=0;i<numpower2.size();i++)
			numpower2[i] = numpower2[i] - 1;
	}
	else if(scOutStat==1 || scOutStat==3)
	{
		for(i=0;i<numpower.size();i++)
			numpower[i] = numpower[i] - 1;
	}

	PolyAdd(numcoef3,numpower3,numcoef,numpower,numcoef2,numpower2);
	cout << "to print infinity coef" << endl;
//	cout << endl << endl;
	cout << "-----final TF-----" << endl;
	cout << "num: " << endl;
	PolyPrint(numcoef3,numpower3);
	cout << "den: " << endl;
	PolyPrint(dencoef,denpower);
	//PolyAnalysis(numcoef3,numpower3,dencoef,denpower);
}

void GPDD::EvaluateInfinityCoefNode(GpddNode* p,bool flag)
{
// InfinityOrder, zeroMarki, of symbol,  InfinityOrder of Node. 
//	cout << "-->>to visit node:" << p->GetSymbol()->Name()<< endl;
	if(p->Marked()==flag)
	{
		return;// p->GetValue().real();
	}
	if(p->GetLeft()->Marked()!=flag)
	{
		this->EvaluateInfinityCoefNode(p->GetLeft(),flag);
	}
	if(p->GetRight()->Marked()!=flag)
	{
		this->EvaluateInfinityCoefNode(p->GetRight(),flag);
	}
	double value = p->GetSymbol()->Value();
	int infinityOrder = p->GetSymbol()->Infinity();
	if(p->GetSymbol()->ZeroMarked()==true)
	{
//		cout << "\tthis symbol is zero marked" << endl;
		// assign the right node value and label
		value = p->GetSignR() * p->GetRight()->GetValue().real();
		infinityOrder = p->GetRight()->GetInfinityOrder();
	}
	else
	{
		infinityOrder += p->GetLeft()->GetInfinityOrder();;
		if(infinityOrder>p->GetRight()->GetInfinityOrder())
		{
//			cout << "\tleft+it > right" << endl;
			value *= p->GetSignL() * p->GetLeft()->GetValue().real();
		}
		else if(infinityOrder<p->GetRight()->GetInfinityOrder())
		{
//			cout << "\tleft+it < right" << endl;
			value = p->GetSignR() * p->GetRight()->GetValue().real();
			infinityOrder = p->GetRight()->GetInfinityOrder();
		}
		else 
		{
//			cout << "\tleft+it = right" << endl;
			value *= p->GetSignL() * p->GetLeft()->GetValue().real();
			value += p->GetSignR() * p->GetRight()->GetValue().real();	
		}
	}
	// update node value and infinity order
	p->SetValue(CPLX(value,0));
	p->SetInfinityOrder(infinityOrder);
	p->Mark(flag);
//	cout << "<<--leave node:" << p->GetSymbol()->Name() << endl;
	return;
}

void GPDD::InfinityExpandNode(GpddNode* p,bool flag)
{
	//cout << "infinity expand, to visit node:" << p->GetSymbol()->Name() << endl;
	if(p->Marked()==flag)
	{
		//cout << "leave node:" << p->GetSymbol()->Name() << endl;
		return;
	}
	if(p->GetLeft()->Marked()!=flag)
	{
		//cout << "to visit left:" << p->GetSymbol()->Name() << "->left:" << p->GetLeft()->GetSymbol()->Name() << endl; 
		InfinityExpandNode(p->GetLeft(),flag);
	}
	if(p->GetRight()->Marked()!=flag)
	{
		//cout << "to visit right:" << p->GetSymbol()->Name() << "->right:" << p->GetRight()->GetSymbol()->Name() << endl; 
		InfinityExpandNode(p->GetRight(),flag);
	}
	CoefNode* cn = new CoefNode();
	CoefMultAdd(cn,p,p->GetSymbol()->Infinity());
	p->SetCoef(cn);
	p->Mark(flag);
	//cout << "leave node:" << p->GetSymbol()->Name() << endl;
}

void GPDD::PrintNodeCoef(const GpddNode* p)
{
	list<GpddNode*> termPath;
	int i = 0, m = 0;
	CoefNode* cn = p->GetCoef();
	m = cn->scoef.size();
	int sign = 1;
	for(i=0;i<m;i++)
	{
		cout << "power: " << cn->spower[i] << endl;
		cout << "coef : " << endl;
		PrintTermR(termPath,sign,cn->scoef[i]);
		termPath.clear();
	}
	cout << endl;
}

void GPDD::PrintCoef()
{
	list<GpddNode*> termPath;
	int sign = 1;
	int i = 0, m = 0;
	cout << "root 0:" << endl;
	cout << "numerator coef: " << endl;
	CoefNode* cn = root->GetLeft()->GetCoef();
	m = cn->scoef.size();
	for(i=0;i<m;i++)
	{
		cout << "power: " << cn->spower[i] << endl;
		cout << "coef : " << endl;
		PrintTermR(termPath,sign,cn->scoef[i]);
		termPath.clear();
	}

	cout << endl;
	cout << "denominator coef:" << endl;
	cn = root->GetRight()->GetCoef();
	m = cn->scoef.size();
	for(i=0;i<m;i++)
	{
		cout << "power: " << cn->spower[i] << endl;
		cout << "coef : " << endl;
		PrintTermR(termPath,sign,cn->scoef[i]);
		termPath.clear();
	}
	
	if(root2==NULL)
		return;
	sign = 1;
	i = 0;
	m = 0;
	termPath.clear();
	cout << "root 2:" << endl;
	cout << "numerator coef: " << endl;
	cn = root2->GetLeft()->GetCoef();
	cout << "root2:" << root2 << endl;
	if(cn==NULL)
	{	
		cout << "root 2 empty" << endl;
		return;
	}
	m = cn->scoef.size();
	cout << m << endl;
	for(i=0;i<m;i++)
	{
		cout << "power: " << cn->spower[i] << endl;
		cout << "coef : " << endl;
		PrintTermR(termPath,sign,cn->scoef[i]);
		termPath.clear();
	}

	cout << endl;
	cout << "denominator coef:" << endl;
	cn = root2->GetRight()->GetCoef();
	m = cn->scoef.size();
	for(i=0;i<m;i++)
	{
		cout << "power: " << cn->spower[i] << endl;
		cout << "coef : " << endl;
		PrintTermR(termPath,sign,cn->scoef[i]);
		termPath.clear();
	}


}

void GPDD::EvaluateCoef()
{
//	cout << "Evaluate Coef Begin" << endl;

	numcoef.clear();
	numpower.clear();
	dencoef.clear();
	denpower.clear();
	numcoef2.clear();
	numpower2.clear();
	dencoef2.clear();
	denpower2.clear();
	numcoef3.clear();
	numpower3.clear();	

	int i = 0, n = 0, m = 0;
	int small;
	bool flag;
root_0:	
	CoefNode* cn = root->GetLeft()->GetCoef();
	CoefNode* cm = root->GetRight()->GetCoef();
	n = cn->scoef.size();
	if(n==0)
	{
		cout << "root 0 empty num" << endl;
		goto root_2;
	}
	numpower = cn->spower;
	m = cm->scoef.size();
	denpower = cm->spower;
	
	small = denpower[0];
	if(numpower[0]<small)
		small = numpower[0];

	flag = cn->scoef[0]->Marked();
	flag = !flag;
	pGpddNodeOne->Mark(flag);
	pGpddNodeZero->Mark(flag);

	for(i=0;i<n;i++)
	{	
		numcoef.push_back(EvaluateCoefNode(cn->scoef[i],flag));
		numpower[i] = (numpower[i]-small);
	}
	for(i=0;i<m;i++)
	{	
		dencoef.push_back(EvaluateCoefNode(cm->scoef[i],flag));
		denpower[i] = (denpower[i]-small);
	}
/*
	cout << "small order comp = " << small << endl;
	cout << "num: " << endl;
	PolyPrint(numcoef,numpower);
	cout << "den: " << endl;
	PolyPrint(dencoef,denpower);
*/
root_2:
	cn = root2->GetLeft()->GetCoef();
	if(cn==NULL)
		goto root_3;
	cm = root2->GetRight()->GetCoef();
	n = cn->scoef.size();
	if(n==0)
	{
		cout << "root 2 empty num" << endl;
		goto root_3;
	}
	numpower2 = cn->spower;
	m = cm->scoef.size();
	denpower2 = cm->spower;
	
	small = denpower2[0];
	if(numpower2[0]<small)
		small = numpower2[0];

	for(i=0;i<n;i++)
	{	
		numcoef2.push_back(EvaluateCoefNode(cn->scoef[i],flag));
		numpower2[i] = (numpower2[i]-small);
	}
	for(i=0;i<m;i++)
	{	
		dencoef2.push_back(EvaluateCoefNode(cm->scoef[i],flag));
		denpower2[i] = (denpower2[i]-small);
	}
/*
	cout << "small order comp = " << small << endl;
	cout << "num: " << endl;
	PolyPrint(numcoef2,numpower2);
	cout << "den: " << endl;
	PolyPrint(dencoef2,denpower2);
*/
root_3:
	int scOutStat = ckt->GetScOutStat();
	i = 0;
	if(scOutStat==0 || scOutStat==2)
	{
		for(i=0;i<numpower2.size();i++)
			numpower2[i] = numpower2[i] - 1;
	}
	else if(scOutStat==1 || scOutStat==3)
	{
		for(i=0;i<numpower.size();i++)
			numpower[i] = numpower[i] - 1;
	}

	//vector<double> numcoef3;
	//vector<int> numpower3;
	PolyAdd(numcoef3,numpower3,numcoef,numpower,numcoef2,numpower2);
//	cout << endl << endl;
	cout << "-----final TF-----" << endl;
	cout << "num: " << endl;
	PolyPrint(numcoef3,numpower3);
	cout << "den: " << endl;
	PolyPrint(dencoef,denpower);

	//PolyAnalysis(numcoef3,numpower3,dencoef,denpowerx);

}

double GPDD::EvaluateCoefNode(GpddNode* p, bool flag)
{
	if(p->Marked()==flag)
		return (p->GetValue().real());
	double value = p->GetSymbol()->GetValue();
	value *= p->GetSignL() * EvaluateCoefNode(p->GetLeft(),flag);
	value += p->GetSignR() * EvaluateCoefNode(p->GetRight(),flag);
	p->SetValue(CPLX(value,0));
//	cout << "symbol:" << p->GetSymbol()->Name() << "\tvalue:" << value << endl;
	p->Mark(flag);
	return value;
}

double GPDD::EvaluateSensCoefNode(GpddNode* p,int updated,Symbol* target)
{
//	cout << "sens, target:" << target->Name() << "\t" << "current node:" << p->GetSymbol()->Name() << endl;
//	cout << "to visit:" << p->GetSymbol()->Name() << "\t" << p->GetSymbol()->Index() << endl;
	double value = 0;
//	cout << "sens, target:" << target->Name() << "\t" << "current node:" << p->GetSymbol()->Name() << endl;
	if(p->GetSymbol()->Index()>target->Index())
	{
//		cout << "but this path no target symbol" << endl;
		return 0;
	}
	else if(p->Marked()==updated)
	{
//		cout << "have been updated" << endl;
		value = (p->GetValue().real());
		return value;
	}
	else if(p->GetSymbol()->Index()==target->Index())
	{
//		cout << "this is target symbol" << endl;
		value = p->GetSignL()*p->GetLeft()->GetValue().real();
//		cout << "left symbol is:" << p->GetLeft()->GetSymbol()->Name() << "\t"<<p->GetLeft()->GetSymbol()->Index()<< endl;
//		cout << value << endl;
	}
	else
	{
//		cout << "before reach target" << endl;
		value = p->GetSymbol()->GetValue();
		value *= p->GetSignL() * EvaluateSensCoefNode(p->GetLeft(),updated,target);
		value += p->GetSignR() * EvaluateSensCoefNode(p->GetRight(),updated,target);
//		cout << "sens, target:" << target->Name() << "\t" << "current node:" << p->GetSymbol()->Name() << endl;
//		cout << "after reach target" << endl;
	}
	p->SetValue(CPLX(value,0));
//	cout << "to set node value:" << p->GetSymbol()->Name() << "\t" << p->GetValue() << endl;
	p->Mark(updated);
	return value;
}

// sens power , same with H(s)
void GPDD::EvaluateCoefSens(Symbol* target,vector<double>& sens_numcoef,vector<double>& sens_dencoef)
{
	int i = 0, n = 0, m = 0;

	vector<double> numcoef_1;
	vector<double> numcoef_2;
	vector<int> tmp_power;

//	cout << "here sens begin" << endl;

	CoefNode* cn = root->GetLeft()->GetCoef();
	CoefNode* cm = root->GetRight()->GetCoef();
	
	int updated = cn->scoef[0]->Marked();
	updated += 1;
//	cout << "update:" << updated << endl;
	pGpddNodeOne->Mark(updated);
//	cout << "one:" << pGpddNodeOne->GetSymbol()->Index() << endl;
	pGpddNodeZero->Mark(updated);
//	cout << "zero:" << pGpddNodeZero->GetSymbol()->Index() << endl;

	n = cn->scoef.size();
	m = cm->scoef.size();

//	cout << "begin sens .." << endl;

	for(i=0;i<n;i++)
	{	
		numcoef_1.push_back(EvaluateSensCoefNode(cn->scoef[i],updated,target));
	}
	cout << "root 0(num):" << endl;
	PolyPrint(numcoef_1,numpower);

	for(i=0;i<m;i++)
	{	
		sens_dencoef.push_back(EvaluateSensCoefNode(cm->scoef[i],updated,target));
	}

	cout << "root 0(den):" << endl;
	PolyPrint(sens_dencoef,denpower);

	// another root
	cn = root2->GetLeft()->GetCoef();
	cm = root2->GetRight()->GetCoef();
	n = cn->scoef.size();
	m = cm->scoef.size();
	for(i=0;i<n;i++)
	{	
		numcoef_2.push_back(EvaluateSensCoefNode(cn->scoef[i],updated,target));
	}
	cout << "root 2(num):" << endl;
	PolyPrint(numcoef_2,numpower2);
	/*
	for(i=0;i<m;i++)
	{	
		dencoef2.push_back(EvaluateCoefNode(cm->scoef[i],flag));
	}
	*/
	// reuse power of H(s)
	PolyAdd(sens_numcoef,tmp_power,numcoef_1,numpower,numcoef_2,numpower2);
	cout << endl;// << endl;
	cout << "-----final Sens TF-----" << endl;
	cout << "num: " << endl;
	PolyPrint(sens_numcoef,numpower3);
	cout << "den: " << endl;
	PolyPrint(sens_dencoef,denpower);
}


void GPDD::ACCoefAnalysis()
{
	double theta = 0;
//	double fclk = 30e6;	// 30 MHz
	int N = 100;
	vector<double> freqArray(N,0);
	vector<double> ampArray(N,0);
	vector<double> faiArray(N,0);
	
	vector<double> numcoef;
	vector<int> numpower;
	vector<double> dencoef;
	vector<int> denpower;
	//EvaluateCoef(numcoef,numpower,dencoef,denpower);
	EvaluateCoef();

	int i = 0, j = 0, m = 0, n = 0;
	n = numcoef.size();
	m = dencoef.size();
	int maxi = denpower[m];
	if(maxi<numpower[n])
		maxi = numpower[n];
	vector<CPLX> zm(maxi+1);

	CPLX z(0,0);
	CPLX tnum(0,0), tden(0,0);
	CPLX Hz(0,0);
	for(i=0;i<N;i++)
	{
		z = CPLX(cos(theta),sin(theta));
		freqArray[i] = theta; 
		theta += 0.0314;
		zm[0] = CPLX(1,0);
		for(j=1;j<=maxi;j++)
			zm[j] = zm[j-1] * z;
		tnum = CPLX(0,0);
		for(j=0;j<n;j++)
			tnum += numcoef[j] * zm[numpower[j]];
		tden = CPLX(0,0);
		for(j=0;j<m;j++)
			tden += dencoef[j] * zm[numpower[j]];
		Hz = tnum / tden;
		ampArray[i] = abs(Hz);
		faiArray[i] = arg(Hz)*180/M_PI;
	}

	string filename = "res_ac_data.txt";
	fstream file(filename,ios::out);
	for(unsigned int i=0;i<freqArray.size();i++)
	{
		file << setw(12) << setiosflags(ios::scientific) << setprecision(6) << freqArray[i] << "\t" << ampArray[i] << "\t" << faiArray[i] << endl;
	}
}
