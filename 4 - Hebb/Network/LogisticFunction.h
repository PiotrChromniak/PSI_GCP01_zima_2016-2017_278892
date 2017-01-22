#pragma once
#include "ActivationFunction.h"
class LogisticFunction :
	public ActivationFunction
{
public:
	virtual double function(const double) const;
	virtual double frstDerivative(const double) const;
	virtual double scndDerivative(const double) const;
};

