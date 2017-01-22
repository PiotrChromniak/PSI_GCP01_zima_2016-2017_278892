#pragma once
#include <vector>
#include <random>
#include "Sample.h"
#include "ActivationFunction.h"
#include <math.h>
class Neuron
{
	static double thresholdUniform(double);
	static double thresholdBipolar(double);
	static double sigmoidSymmetric(double);
	static double sigmoid(double);

	std::vector<double> _weights;
	double _LEARINING_RATE;
	double _bias;

	double (*_function)(double);

public:
	Neuron(int = 1, ActivationFunction = ActivationFunction::THRESHOLD_UNIFORM, double = 0.1);
	void setLearningRate(double);
	double calculateOutput(Sample&);
	void updateWeights(Sample&, double);
};