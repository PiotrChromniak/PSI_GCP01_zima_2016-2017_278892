#pragma once
#include <vector>
class Sample
{
public:
	std::vector<double> inputs;
	double result;
	Sample(int = 1);
	Sample(std::vector<double>&, double);
};	