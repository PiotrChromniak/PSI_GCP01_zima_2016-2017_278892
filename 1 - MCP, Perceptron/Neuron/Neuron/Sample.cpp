#include "Sample.h"

Sample::Sample(int nInputs)
{
	inputs.resize(nInputs);
}

Sample::Sample(std::vector<double> &weights, double result_) : result(result_)
{
	inputs = weights;
}
