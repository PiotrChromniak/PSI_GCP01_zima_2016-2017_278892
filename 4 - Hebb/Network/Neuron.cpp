#include "Neuron.h"


Neuron::Neuron(ActivationFunction &function, int inputCount) : _f(function)
{
	std::uniform_real_distribution<double> rand(0.0, 1.0);
	std::mt19937_64 engi;
	_weights.resize(inputCount);
	for (auto& weight : _weights)
		weight = rand(engi);
	_bias = rand(engi);
}

Neuron::Neuron(ActivationFunction &function, const int inputNum, std::uniform_real_distribution<double>&rand, std::mt19937_64 &engi) : _f(function)
{
	_weights.resize(inputNum);
	for (auto& weight : _weights)
		weight = rand(engi);
	_bias = rand(engi);
}

double Neuron::getOutput(const std::vector<double>& inputs) const
{
	double sum = _bias;
	auto inputIter = inputs.cbegin();
	for (auto const& weight : _weights) {
		sum += weight * (*inputIter);
		++inputIter;
	}
	return _f.function(sum);
}

void Neuron::updateWeightsHebb(const std::vector<double> &x, const double &y, const double &learningRate)
{
	auto xIt = x.cbegin();
	for (auto &weight : _weights){
		weight += learningRate * y * *xIt;
		++xIt;
	}
}
