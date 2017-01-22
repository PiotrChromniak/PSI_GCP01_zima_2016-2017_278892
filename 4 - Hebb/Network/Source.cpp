#include "Network.h"
#include "LogisticFunction.h"

int main() { 
	
	std::vector<int> v = { 4,8,3,2 };
	std::vector<double> in = { 1,3,2,4 };
	Network n(v, LogisticFunction(), LogisticFunction());
	for (int i = 0; i < 10; ++i) {
		auto out = n.getOutput(in);
		n.updateWeights();
	}
	return 0; 
}