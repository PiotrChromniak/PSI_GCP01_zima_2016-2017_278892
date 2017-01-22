#include "Neuron.h"


double Neuron::thresholdUniform(double x)
{	return x >= 0.0 ? 1.0 : 0.0; }

double Neuron::thresholdBipolar(double x)
{	return x >= 0.0 ? 1.0 : -1.0; }

double Neuron::sigmoidSymmetric(double x)
{	return tanh(x); }

double Neuron::sigmoid(double x)
{	return 1.0/(1.0 + exp(-x)); }

double Neuron::calculateOutput(Sample &sample)
{
	double sum = _bias;
	auto inputIt = sample.inputs.cbegin();
	for (auto& weight : _weights) {
		sum += weight * (*inputIt);
		++inputIt;
	}
	return _function(sum);
}

void Neuron::updateWeights(Sample &sample, double error)
{
	auto sampleIt = sample.inputs.cbegin();
	for (auto& weight : _weights) {
		weight += _LEARINING_RATE * error * *sampleIt;
		++sampleIt;
	}
	_bias += _LEARINING_RATE * error;
}

Neuron::Neuron(int nInput, ActivationFunction activationFunction, double learningRate) : _LEARINING_RATE(learningRate)
{
	std::uniform_real_distribution<double> rand(0.0, 1.0);
	std::default_random_engine engi;
	_weights.resize(nInput);
	for (auto& weight : _weights) {
		weight = rand(engi);
	}
	_bias = rand(engi);
	_function = [&]() {
		switch (activationFunction) {
				case ActivationFunction::SIGMOID:
					return Neuron::sigmoid;
				case ActivationFunction::SIGMOID_SYMMETRIC:
					return Neuron::sigmoidSymmetric;
				case ActivationFunction::THRESHOLD_BIPOLAR:
					return Neuron::thresholdBipolar;
				default:
					return Neuron::thresholdUniform;
		}	
	}();
}

void Neuron::setLearningRate(double learningRate)
{
	_LEARINING_RATE = learningRate;
};