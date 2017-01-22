#pragma once
class ActivationFunction
{
public:
	virtual double function(const double) const = 0 ;
	virtual double frstDerivative(const double) const = 0;
	virtual double scndDerivative(const double) const = 0;
};