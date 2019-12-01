#include <cstdlib>
#include <iostream>

#include "Neuron.h"

int main()
{
	Neuron* input_1 = new Neuron(1);
	Neuron* input_2 = new Neuron(0);

	Neuron* hiden_1 = new Neuron(Neuron::Type::Hidden);
	Neuron* hiden_2 = new Neuron(Neuron::Type::Hidden);

	Neuron* output = new Neuron(Neuron::Type::Output);

	input_1->add_output_connection(hiden_1, 0.45f);
	input_1->add_output_connection(hiden_2, 0.78f);

	input_2->add_output_connection(hiden_1, -0.12f);
	input_2->add_output_connection(hiden_2, 0.13f);

	hiden_1->add_output_connection(output, 1.5f);
	hiden_2->add_output_connection(output, -2.3f);

	input_1->activate();
	input_2->activate();
	hiden_1->activate();
	hiden_2->activate();
	output->activate();

	std::cout << output->output_value();

	return 0;
}