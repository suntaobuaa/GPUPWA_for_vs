#include "GPUFumiliFCN.h"
#include "GPUPWACalculator.h"
#include "GPUPartialWaveAnalysis.h"

GPUFumiliFCN::GPUFumiliFCN(GPUPWACalculator * _calc): mCalc(_calc)
{
	InitAndReset((int)mCalc->GetAnalysis()->GetParameters()->Params().size());
}

GPUFumiliFCN::~GPUFumiliFCN(void)
{
}

void GPUFumiliFCN::EvaluateAll(const std::vector<double> & par){
	EvaluateConst(par);

}


void GPUFumiliFCN::EvaluateConst(const std::vector<double> & par)  {
	double fuck;
	vector<double> your = Gradient();
	vector<double> mother=  Hessian();
	fuck = mCalc->LikelihoodGradientHessian(par, your, mother);
//	fValue = mCalc->LikelihoodGradientHessian(par, fGradient, fHessian);
	SetFCNValue(fuck);


}

double GPUFumiliFCN::operator() (const vector<double> & x) 
{
	EvaluateConst(x);
	//cout <<" fValue in GPUFumiliFCN::operator() "<<fValue<< endl;
	//return fValue;
	return Value();
}

double GPUFumiliFCN::operator() (const vector<double> & x) const 
{
	//EvaluateConst(x);
	//cout <<" fValue in GPUFumiliFCN::operator() "<<fValue<< endl;
	//return fValue;
	return Value();
}
