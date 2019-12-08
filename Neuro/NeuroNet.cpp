#include "NeuroNet.h"

#include <random>

NeuroNet::NeuroNet(int input_nodes, int hidden_nodes, int output_nodes, double training_rate)
{
	this->input_nodes = input_nodes;
	this->hidden_nodes = hidden_nodes;
	this->output_nodes = output_nodes;
	this->training_rate = training_rate;

	wih = Matrix<double>(hidden_nodes, input_nodes);
	who = Matrix<double>(output_nodes, hidden_nodes);

	std::random_device rnd;
	
	for (size_t i = 0; i < wih.getRows(); i++)
	{
		for (size_t j = 0; j < wih.getColumns(); j++)
		{
			double tmp = (double)rnd() / rnd.max() - 0.5;

			wih.put(i, j, tmp);
		}
	}

	for (size_t i = 0; i < who.getRows(); i++)
	{
		for (size_t j = 0; j < who.getColumns(); j++)
		{
			double tmp = (double)rnd() / rnd.max() - 0.5;

			who.put(i, j, tmp);
		}
	}
}

std::vector<double> NeuroNet::query(std::vector<double>& input_values)
{
	Matrix<double> inputs(input_values.size(), 1);

	for (size_t i = 0; i < input_values.size(); i++)
	{
		inputs.put(i, 0, input_values[i]);
	}

	Matrix<double> hidden_inputs = wih * inputs;
	Matrix<double> hidden_outputs(hidden_inputs.getRows(), hidden_inputs.getColumns());

	for (size_t i = 0; i < hidden_outputs.getRows(); i++)
	{
		hidden_outputs.put(i, 0, 1.0 / (1 + exp(-hidden_inputs.get(i, 0))));
	}

	Matrix<double> final_inputs = who * hidden_outputs;
	Matrix<double> final_outputs(final_inputs.getRows(), final_inputs.getColumns());

	for (size_t i = 0; i < final_inputs.getRows(); i++)
	{
		final_outputs.put(i, 0, 1.0 / (1 + exp(-final_inputs.get(i, 0))));
	}

	std::vector<double> result(final_outputs.getRows());

	for (size_t i = 0; i < result.size(); i++)
	{
		result[i] = final_outputs.get(i, 0);
	}

	return result;
}

void NeuroNet::train(std::vector<double>& input_values, std::vector<double>& target_values)
{
	Matrix<double> inputs(input_values.size(), 1);
	Matrix<double> targets(target_values.size(), 1);

	for (size_t i = 0; i < input_values.size(); i++)
	{
		inputs.put(i, 0, input_values[i]);
	}

	for (size_t i = 0; i < target_values.size(); i++)
	{
		targets.put(i, 0, target_values[i]);
	}

	Matrix<double> hidden_inputs = wih * inputs;
	Matrix<double> hidden_outputs(hidden_inputs.getRows(), hidden_inputs.getColumns());

	for (size_t i = 0; i < hidden_outputs.getRows(); i++)
	{
		hidden_outputs.put(i, 0, 1.0 / (1 + exp(-hidden_inputs.get(i, 0))));
	}

	Matrix<double> final_inputs = who * hidden_outputs;
	Matrix<double> final_outputs(final_inputs.getRows(), final_inputs.getColumns());

	for (size_t i = 0; i < final_inputs.getRows(); i++)
	{
		final_outputs.put(i, 0, 1.0 / (1 + exp(-final_inputs.get(i, 0))));
	}

	Matrix<double> output_errors = targets - final_outputs;
	Matrix<double> hidden_errors = who.getTranspose() * output_errors;

	Matrix<double> buff(final_outputs.getRows(), final_outputs.getColumns());
	for (size_t i = 0; i < final_outputs.getRows(); i++)
	{
		for (size_t j = 0; j < final_outputs.getColumns(); j++)
		{
			double tmp = output_errors.get(i, j) * 
						 final_outputs.get(i, j) * 
						 (1 - final_outputs.get(i, j));

			buff.put(i, j, tmp);
		}
	}

	who += buff * hidden_outputs.getTranspose() * training_rate;

	buff = Matrix<double>(hidden_outputs.getRows(), hidden_outputs.getColumns());
	for (size_t i = 0; i < hidden_outputs.getRows(); i++)
	{
		for (size_t j = 0; j < hidden_outputs.getColumns(); j++)
		{
			double tmp = hidden_errors.get(i, j) *
						 hidden_outputs.get(i, j) *
						 (1 - hidden_outputs.get(i, j));

			buff.put(i, j, tmp);
		}
	}

	wih += buff * inputs.getTranspose() * training_rate;
}
