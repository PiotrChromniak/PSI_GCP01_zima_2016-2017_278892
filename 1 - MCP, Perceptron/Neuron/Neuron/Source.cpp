#include <iostream>
#include <fstream>
#include "Sample.h"
#include "Neuron.h"
using namespace std;

int main() {
	fstream file("manwoman.txt", ios::in);
	vector<Sample> samples, validationSamples;
	if (file.good()) {
		int numSamples, numInput, numOutput;
		file >> numSamples >> numInput >> numOutput;
		samples.reserve(numSamples);
		vector<double> inputs(numInput);
		double output;

		for (int i = 0; i < numSamples; ++i) {
			for (auto& input : inputs)
				file >> input;
			file >> output;
			samples.push_back(Sample(inputs, output));
		}
		file.close();
	}
	else {
		cerr << "Error - file openin\n";
		return -1;
	}

	fstream file2("manwoman_validation.txt", ios::in);
	if (file2.good()) {
		int numSamples, numInput, numOutput;
		file2 >> numSamples >> numInput >> numOutput;
		validationSamples.reserve(numSamples);
		vector<double> inputs(numInput);
		double output;

		for (int i = 0; i < numSamples; ++i) {
			for (auto& input : inputs)
				file2 >> input;
			file2 >> output;
			validationSamples.push_back(Sample(inputs, output));
		}
		file2.close();
	}
	else {
		cerr << "Error - file2 opening\n";
		return -1;
	}

	Neuron neuron(samples[0].inputs.size(), ActivationFunction::THRESHOLD_BIPOLAR);
	double DESIRED_ERROR = 0.01;
	int MAX_ITERATIONS = 1000;
	auto iteration = 0;
	auto error = 0.0;
	double globalError, MAPE;

	fstream log("log.txt", ios::out);
	if (log.good()) {
		log << "Iteration MSE MAPE\n";
		do {
			double output;
			globalError = 0.0;
			MAPE = 0.0;
			/* Uczenie */
			for (auto& sample : samples) {
				output = neuron.calculateOutput(sample);
				error = sample.result - output;
				if (error != 0.0) {
					neuron.updateWeights(sample, error);
					globalError += error*error;
					MAPE += fabs(error / sample.result);
				}
			}
			MAPE = MAPE * 100.0 / static_cast<double>(samples.size());

			/*  Wypisanie do logu tekstowego i std::cout  */
			cout << "Epoch: " << iteration << " MSE: " << globalError / static_cast<double>(samples.size()) << " MAPE: " << MAPE << '\n';
			log << "Learning :\n";
			log << iteration << ' ' << globalError / static_cast<double>(samples.size()) << ' ' << MAPE << '\n';

			/* Walidacja na innych danych */
			double globalErrorValid = 0.0;
			double MAPEvalid = 0.0;
			auto under = 0, over = 0;
			for (auto& sample : validationSamples) {
				output = neuron.calculateOutput(sample);
				error = sample.result - output;
				if (error != 0.0) {
					if (output > sample.result) over++;
					else under++;
					globalErrorValid += error*error;
					MAPEvalid += fabs(error / sample.result);
				}
			}
			MAPEvalid = MAPEvalid * 100.0 / static_cast<double>(validationSamples.size());
			/* Wypisanie do logu tekstowego */
			log << "Validating :\n";
			log << iteration << ' ' << globalErrorValid / static_cast<double>(validationSamples.size()) << ' ' << MAPEvalid << '\n';
			log << "Under & Over\n";
			log << under << ' ' << over << '\n';
			++iteration; 
		} while (globalError > DESIRED_ERROR && iteration < MAX_ITERATIONS);
		log.close();
	}
 	return 0;
}