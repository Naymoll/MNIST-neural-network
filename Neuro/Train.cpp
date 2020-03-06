#include "NeuroNet.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <omp.h>
#include <chrono>

int main()
{
	std::fstream in;
	in.open("./mnist_train.csv", std::fstream::in);

	std::vector<std::vector<double>> train_data(60000);

	for (size_t i = 0; i < train_data.size(); i++)
	{
		bool ok = true;
		char* end;
		char* str = new char[3200];
		in.getline(str, 3200, '\n');

		do
		{
			double value = std::strtod(str, &end);
			train_data[i].push_back(value);

			if (*end == ',')
			{
				end++;
				str = end;
			}

		} while (*end != '\0');
	}

	in.close();

	int input_nodes = 784;
	int hidden_nodes = 800;
	int output_nodes = 10;

	double training_rate = 0.1;

	NeuroNet net(input_nodes, hidden_nodes, output_nodes, training_rate);

	int epochs = 5;

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < epochs; i++)
	{
		for (size_t j = 0; j < train_data.size(); j++)
		{
			std::vector<double> inputs(input_nodes);

			for (size_t k = 0; k < input_nodes; k++)
			{
				inputs[k] = train_data[j][k + 1] / 255.0 * 0.99 + 0.01;
			}

			std::vector<double> targets(output_nodes, 0.1);
			targets[train_data[j][0]] = 0.99;

			net.train(inputs, targets);
		}
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto time = end - start;

	std::cout << time.count();

	net.save();

	train_data.clear();

	return 0;
}