#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "NeuroNet.h"

int main()
{
	std::fstream in;
	in.open("./mnist_test_10.csv", std::fstream::in);
	
	std::vector<std::vector<double>> data_mnist(10);

	for (size_t i = 0; i < data_mnist.size(); i++)
	{
		std::string str;
		std::getline(in, str, '\n');
		str.push_back('\n');

		bool ok = true;
		char* end;
		const char* c_str = str.c_str();

		do
		{
			double value = std::strtod(c_str, &end);
			data_mnist[i].push_back(value);

			if (*end == ',')
			{
				end++;
				c_str = end;
			}

		} while (*end != '\n');
	}

	int input_nodes = 784;
	int hidden_nodes = 200;
	int output_nodes = 10;

	double training_rate = 0.2;

	NeuroNet net(input_nodes, hidden_nodes, output_nodes, training_rate);

	int epochs = 5;

	for (size_t i = 0; i < epochs; i++)
	{
		for (size_t j = 0; j < data_mnist.size(); j++)
		{
			std::vector<double> inputs(input_nodes);

			for (size_t k = 0; k < input_nodes; k++)
			{
				inputs[k] = data_mnist[j][k + 1] / 255.0 * 0.99 + 0.01;
			}

			std::vector<double> targets(output_nodes, 0.1);
			targets[data_mnist[j][0]] = 0.99;

			net.train(inputs, targets);
		}
	}

	for (size_t i = 0; i < data_mnist.size(); i++)
	{
		std::vector<double> inputs(input_nodes);

		for (size_t j = 0; j < input_nodes; j++)
		{
			inputs[j] = data_mnist[i][j + 1] / 255.0 * 0.99 + 0.01;
		}

		auto outpots = net.query(inputs);

		double max = 0.0;
		int pos = 0;
		for (size_t j = 0; j < outpots.size(); j++)
		{
			if (outpots[j] > max)
			{
				max = outpots[j];
				pos = j;
			}
		}

		std::cout << "Input = " << data_mnist[i][0] << "; Neural net = " << pos << std::endl;
	}

	return 0;
}