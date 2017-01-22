#pragma once
#include <vector>
#include <random>
#include "Neuron.h"
#include "ActivationFunction.h"
class Layer
{
	std::vector<Neuron> _neurons;
	std::vector<double>& _outputSignal;
public:
	void saveOutputSignal(const std::vector<double>& inputSignal);
	void updateWeightsHebb(const std::vector<double> &inputSignal, const std::vector<double> &outputSignal, const double learningRate);
	Layer(int inputNum, int neuronNum, ActivationFunction &function, std::vector<double>& outputVector, std::uniform_real_distribution<double> &rand, std::mt19937_64 &engi);

};
