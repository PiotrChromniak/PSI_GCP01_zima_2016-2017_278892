#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>


using namespace std;

int main(int argc, char* argv[]) {
	fstream file("train_data.txt", ios::in );
	if (file.good()) {
		int probes, input_count, output_count, noise_level;

		file >> probes >> input_count >> output_count;
		if (argc > 1)	noise_level = atoi(argv[1]);
		else noise_level = 1;

		string output_name = "noise_data";
		if (argc > 1) output_name += argv[1];
		else output_name += '1';
		output_name += ".data";

		fstream file_out;
		file_out.open(output_name, ios::out);

		if (file_out.good()) {
			file_out << probes << ' ' << input_count << ' ' << output_count << '\n';
			srand(time(NULL));

			for (int i = 0; i< probes; ++i) {
				vector<int> input(input_count), output(output_count);
				for (int j = 0; j<input_count; ++j)
					file >> input[j];
				for (int j = 0; j<output_count; ++j)
					file >> output[j];

				bool succes = false;
				int succeses = 0;
				while (succeses < noise_level && !succes) {
					int position = rand() % input_count;
					if (input[position] == 0) {
						input[position] = 1;
						succes = true;
						succeses++;
					}
				}
				for (auto& x : input)
					file_out << x << ' ';
				file_out << '\n';

				for (auto& x : output)
					file_out << x << ' ';
				if(i != probes -1) file_out << '\n';
			}
			file_out.close();

		}
		else cout << "Nie udalo sie utworzyc pliku wyjsciowego\n";
		file.close();
	}
	else cout << "Nie udalo sie otworzyc pliku wejsciowego\n";

	return 0;
}
