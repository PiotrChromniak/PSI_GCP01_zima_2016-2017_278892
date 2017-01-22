#pragma once
#include <vector>
#include "Neuron.h"
#include "Layer.h"
class Network
{
	double _learningRate;
	int _inputSize, _outputSize;
	ActivationFunction &_outputFunction, &_hiddenFunction;
	std::vector<std::vector<double>> _x;
	std::vector<Layer> _layers;
public:
	void updateWeights();
	std::vector<double> getOutput(const std::vector<double> inputs);
	Network(const std::vector<int>&, ActivationFunction&, ActivationFunction&, const double &learningRate = 0.1);
};

