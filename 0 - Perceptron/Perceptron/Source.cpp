#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <fstream>
#include <vector>
#include "Sample.h"
using namespace std;

int calcOutput(float[], float, float, float);

int main() {
	const float LEARNING_RATE = 0.1f;
	const unsigned int MAX_ITERATIONS = 100;
	int samplesCount, epoch;
	vector<Sample> samples;

	fstream file;
	file.open("data.txt");
	if (file.good()) {
		file >> samplesCount;
		samples.reserve(samplesCount);
		float t_x, t_y, t_z, t_res;
		for (int i = 0; i < samplesCount; ++i) {
			file >> t_x >> t_y >> t_z >> t_res;
			samples.push_back(Sample(t_x, t_y, t_z, t_res));
		}
	}
	else return 1;

	srand(time(NULL));
	float weight[4];
	weight[0] = (float)rand() / (float)RAND_MAX;
	weight[1] = (float)rand() / (float)RAND_MAX;
	weight[2] = (float)rand() / (float)RAND_MAX;
	weight[3] = (float)rand() / (float)RAND_MAX;

	epoch = 0;
	float e = 0.0f, error, MAPE;
	int out;
	vector<Sample>::iterator it;

	do {
		it = samples.begin();
		error = 0.0f;
		MAPE = 0.0f;

		for (; it != samples.end(); ++it) {
			out = calcOutput(weight, (*it).x, (*it).y, (*it).z);
			e = (*it).result - out;
			
			weight[0] += LEARNING_RATE * e * (*it).x;
			weight[1] += LEARNING_RATE * e * (*it).y;
			weight[2] += LEARNING_RATE * e * (*it).z;
			weight[3] += LEARNING_RATE * e;

			MAPE += fabs(e / float(out));
			error += (e*e);
		}
		MAPE = MAPE * 100.0f / (float)samples.size();
		++epoch;
		cout << "Epoch: " << epoch << " MSE: " << error / (float)samples.size() << " MAPE: " << MAPE << endl;
		
	} while (error != 0.0f && epoch <= MAX_ITERATIONS);
	cout << " euqation: " << weight[0] << "*x + " << weight[1] << "*y + " << weight[2] << "*z + " << weight[3] << " = 0\n";
	system("pause");
	return 0;
}

int calcOutput(float w[], float x, float y, float z)
{
	float sum = x*w[0] + y*w[1] + z*w[2] + w[3];
	return (sum >= 0) ? 1 : -1;
}