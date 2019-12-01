#pragma once

#include "Neuron.h"

#include <vector>
#include <tuple>

class Connections
{
public:
	explicit Connections();
	~Connections();

	void add_input_connection(Neuron* input_neuron);
	void erase_input_connection(Neuron* input_neuron);

	void add_output_connection(Neuron* output_neuron, float width);
	void erase_output_connection(Neuron* output_neuron);

	void clear_connections();

	std::vector<Neuron*> input_connections();
	float connection_width(Neuron* output_neuron);

private:
	std::vector<Neuron*> input_neurons;
	std::vector<std::tuple<Neuron*, float>> output_neurons;
};

