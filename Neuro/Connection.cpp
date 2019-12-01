#include "Connection.h"

Connections::Connections()
{
}

Connections::~Connections()
{
}

void Connections::add_input_connection(Neuron* input_neuron)
{
	for (Neuron* var : input_neurons)
	{
		if (var == input_neuron)
			return;
	}

	input_neurons.push_back(input_neuron);
}

void Connections::erase_input_connection(Neuron* input_neuron)
{
	for (auto iter = input_neurons.begin(); iter != input_neurons.end(); iter++)
	{
		if (*iter == input_neuron)
		{
			input_neurons.erase(iter);
			return;
		}
	}
}

void Connections::add_output_connection(Neuron* output_neuron, float width)
{
	for (auto var : output_neurons)
	{
		Neuron* _neuron;
		float _width;
		std::tie(_neuron, _width) = var;
		if (_neuron == output_neuron)
			return;
	}

	output_neurons.push_back(std::make_tuple(output_neuron, width));
}

void Connections::erase_output_connection(Neuron* output_neuron)
{
	for (auto iter = output_neurons.begin(); iter != output_neurons.end(); iter++)
	{
		Neuron* _neuron;
		float _width;
		std::tie(_neuron, _width) = *iter;
		
		if (_neuron == output_neuron)
		{
			output_neurons.erase(iter);
			return;
		}
	}
}

void Connections::clear_connections()
{
	input_neurons.clear();
	output_neurons.clear();
}

std::vector<Neuron*> Connections::input_connections()
{
	return input_neurons;
}

float Connections::connection_width(Neuron* output_neuron)
{
	for (auto iter = output_neurons.begin(); iter != output_neurons.end(); iter++)
	{
		Neuron* _neuron;
		float _width;
		std::tie(_neuron, _width) = *iter;

		if (_neuron == output_neuron)
		{
			return _width;
		}
	}

	return 0.0f;
}
