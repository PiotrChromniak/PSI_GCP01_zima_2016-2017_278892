#include "LogisticFunction.h"
#include <math.h>

double LogisticFunction::function(double x) const
{
	return 1.0 / (1.0 + exp(-x));
}

double LogisticFunction::frstDerivative(double x) const
{
	return function(x)*(1.0 - function(x));
}

double LogisticFunction::scndDerivative(double x) const
{
	return frstDerivative(x)*(1.0 - 2.0*function(x));
}
