#include "Network.h"

void Network::updateWeights()
{
	auto inputIt = _x.cbegin(), outputIt = inputIt + 1;
	for (auto& layer : _layers) {
		layer.updateWeightsHebb(*(inputIt), *(outputIt), _learningRate);
		++inputIt;
		++outputIt;
	}
}

std::vector<double> Network::getOutput(const std::vector<double> inputs)
{
	_x[0] = inputs;
	auto inputIt = _x.begin();
	for (auto& neuron : _layers) {
		neuron.saveOutputSignal(*(inputIt));
		++inputIt;
	}
	return std::vector<double>(_x.back());
}

Network::Network(const std::vector<int> &layersSizes, ActivationFunction &hiddenLayerFunction, ActivationFunction &outputLayerFunction, const double& learningRate) : _hiddenFunction(hiddenLayerFunction), _outputFunction(outputLayerFunction), _learningRate(learningRate)
{
	// Initialization 
	_inputSize = layersSizes.front();
	_outputSize = layersSizes.back();
	_x.resize(layersSizes.size());
	
	// Matrix initialization
	auto xIter = _x.begin();
	for (auto const& layerSize : layersSizes) {
		(*xIter).resize(layerSize);
		++xIter;
	}

	std::uniform_real_distribution<double> rand(0.0, 1.0);
	std::mt19937_64 engi;

	// Neural net initialization
	_layers.reserve(layersSizes.size() - 1);
	for (size_t i = 0; i < _layers.capacity(); ++i) {
		if(i != _layers.capacity()-1)
			_layers.push_back(Layer(layersSizes[i], layersSizes[i + 1], hiddenLayerFunction, _x[i + 1], rand, engi));
		else
			_layers.push_back(Layer(layersSizes[i], layersSizes[i + 1], outputLayerFunction, _x[i + 1], rand, engi));
	}
}
