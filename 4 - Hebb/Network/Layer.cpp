#include "Layer.h"

Layer::Layer(int inputNum, int neuronNum, ActivationFunction &function, std::vector<double> &outputVector, std::uniform_real_distribution<double>&rand, std::mt19937_64 &engi) : _outputSignal(outputVector)
{
	_neurons.reserve(neuronNum);
	for (auto i = 0; i < neuronNum; ++i)
		_neurons.push_back(Neuron(function, inputNum, rand, engi));
}

void Layer::saveOutputSignal(const std::vector<double>& inputSignal)
{
	auto neuronIt = _neurons.cbegin();
	auto outputIt = _outputSignal.begin();
	for (; neuronIt != _neurons.cend(); ++neuronIt, ++outputIt)
		*outputIt = (*neuronIt).getOutput(inputSignal);
}

void Layer::updateWeightsHebb(const std::vector<double>& inputSignal, const std::vector<double>& outputSignal, const double learningRate)
{
	auto outputIt = outputSignal.cbegin();
	for (auto & neuron : _neurons)
		neuron.updateWeightsHebb(inputSignal, *(outputIt++), learningRate);
}