#include "NeuroNet.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <omp.h>
#include <chrono>

int main()
{
	std::fstream in;
	in.open("./mnist_test.csv", std::fstream::in);

	std::vector<std::vector<double>> test_data(10000);

	for (size_t i = 0; i < test_data.size(); i++)
	{
		bool ok = true;
		char* end;
		char* str = new char[3200];
		in.getline(str, 3200, '\n');

		do
		{
			double value = std::strtod(str, &end);
			test_data[i].push_back(value);

			if (*end == ',')
			{
				end++;
				str = end;
			}

		} while (*end != '\0');
	}

	NeuroNet net;
	net.load();

	int input_nodes = 784, ok = 0;

	auto start = std::chrono::high_resolution_clock::now();

	for (size_t i = 0; i < test_data.size(); i++)
	{
		std::vector<double> inputs(input_nodes);

		for (size_t j = 0; j < input_nodes; j++)
		{
			inputs[j] = test_data[i][j + 1] / 255.0 * 0.99 + 0.01;
		}

		auto outputs = net.query(inputs);

		double max = 0.0;
		int pos = 0;
		for (size_t j = 0; j < outputs.size(); j++)
		{
			if (outputs[j] > max)
			{
				max = outputs[j];
				pos = j;
			}
		}

		if (pos == test_data[i][0])
			ok++;
		
		//Output
		//std::cout << test_data[i][0] << " = Input\n" << pos << " = Neural net" << std::endl;
	}

	//Accuracy output
	//std::cout << std::endl << "Accuracy: " << (double)ok / test_data.size() * 100 << "%";

	auto end = std::chrono::high_resolution_clock::now();
	auto time = end - start;

	std::cout << std::endl << "Time: " << time.count() << "ns" << std::endl;

	return 0;
}