#pragma once
#include <vector>
#include "ActivationFunction.h"
#include <random>

class Neuron
{
	std::vector<double> _weights;
	double _bias;
	ActivationFunction& _f;
public:
	Neuron(ActivationFunction&, const int);
	Neuron(ActivationFunction&, const int, std::uniform_real_distribution<double>&, std::mt19937_64&);
	double getOutput(const std::vector<double>&) const;
	void updateWeightsHebb(const std::vector<double>&, const double&, const double&);
};

