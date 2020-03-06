#include "NeuroNet.h"

#include <random>
#include <fstream>

NeuroNet::NeuroNet()
{
	input_nodes = 0;
	hidden_nodes = 0;
	output_nodes = 0;
	training_rate = 0.0;
}

NeuroNet::NeuroNet(int input_nodes, int hidden_nodes, int output_nodes, double training_rate)
{
	this->input_nodes = input_nodes;
	this->hidden_nodes = hidden_nodes;
	this->output_nodes = output_nodes;
	this->training_rate = training_rate;

	wih = Matrix<double>(hidden_nodes, input_nodes);
	who = Matrix<double>(output_nodes, hidden_nodes);

	wih_buffer = Matrix<double>(hidden_nodes, input_nodes);
	who_buffer = Matrix<double>(output_nodes, hidden_nodes);

	std::random_device rnd;
	std::mt19937 gen(rnd());
	std::normal_distribution<double> nd(0.0, std::pow(hidden_nodes, -0.5));
	
	for (size_t i = 0; i < wih.rows(); i++)
	{
		for (size_t j = 0; j < wih.columns(); j++)
		{
			wih.insert(i, j, nd(gen));
		}
	}

	nd = std::normal_distribution<double>(0.0, std::pow(output_nodes, -0.5));

	for (size_t i = 0; i < who.rows(); i++)
	{
		for (size_t j = 0; j < who.columns(); j++)
		{
			who.insert(i, j, nd(gen));
		}
	}
}

std::vector<double> NeuroNet::query(std::vector<double>& input_values)
{
	Matrix<double> inputs(input_values.size(), 1);

	for (size_t i = 0; i < input_values.size(); i++)
	{
		inputs.insert(i, 0, input_values[i]);
	}

	Matrix<double> hidden_inputs = Matrix<double>::dot(wih, inputs);
	Matrix<double> hidden_outputs(hidden_inputs.rows(), hidden_inputs.columns());

	for (size_t i = 0; i < hidden_outputs.rows(); i++)
	{
		hidden_outputs.insert(i, 0, 1.0 / (1 + exp(-hidden_inputs(i, 0))));
	}

	Matrix<double> final_inputs = Matrix<double>::dot(who, hidden_outputs);
	Matrix<double> final_outputs(final_inputs.rows(), final_inputs.columns());

	for (size_t i = 0; i < final_inputs.rows(); i++)
	{
		final_outputs.insert(i, 0, 1.0 / (1 + exp(-final_inputs(i, 0))));
	}

	std::vector<double> result(final_outputs.rows());

	for (size_t i = 0; i < result.size(); i++)
	{
		result[i] = final_outputs(i, 0);
	}

	return result;
}

void NeuroNet::train(std::vector<double>& input_values, std::vector<double>& target_values)
{
	Matrix<double> inputs(input_values.size(), 1);
	Matrix<double> targets(target_values.size(), 1);

	for (size_t i = 0; i < input_values.size(); i++)
	{
		inputs.insert(i, 0, input_values[i]);
	}

	for (size_t i = 0; i < target_values.size(); i++)
	{
		targets.insert(i, 0, target_values[i]);
	}

	Matrix<double> hidden_inputs = Matrix<double>::dot(wih, inputs);
	Matrix<double> hidden_outputs(hidden_inputs.rows(), hidden_inputs.columns());

	for (size_t i = 0; i < hidden_outputs.rows(); i++)
	{
		hidden_outputs.insert(i, 0, 1.0 / (1 + exp(-hidden_inputs(i, 0))));
	}

	Matrix<double> final_inputs = Matrix<double>::dot(who, hidden_outputs);
	Matrix<double> final_outputs(final_inputs.rows(), final_inputs.columns());

	for (size_t i = 0; i < final_inputs.rows(); i++)
	{
		final_outputs.insert(i, 0, 1.0 / (1 + exp(-final_inputs(i, 0))));
	}

	Matrix<double> output_errors = targets - final_outputs;
	Matrix<double> hidden_errors = Matrix<double>::dot(who.get_transpose(), output_errors);

	Matrix<double> buff = output_errors * final_outputs;

	for (size_t i = 0; i < final_outputs.rows(); i++)
	{
		for (size_t j = 0; j < final_outputs.columns(); j++)
		{
			buff.insert(i, j, buff(i,j) * (1 - final_outputs(i, j)));
		}
	}

	who += Matrix<double>::dot(buff, hidden_outputs.get_transpose()) * training_rate;

	buff = hidden_errors * hidden_outputs;

	for (size_t i = 0; i < hidden_outputs.rows(); i++)
	{
		for (size_t j = 0; j < hidden_outputs.columns(); j++)
		{
			buff.insert(i, j, buff(i,j) * (1 - hidden_outputs(i, j)));
		}
	}
	
	wih += Matrix<double>::dot(buff, inputs.get_transpose()) * training_rate;
}

void NeuroNet::save()
{
	std::fstream out;
	out.open("./width.txt", std::fstream::out | std::fstream::trunc);

	out << input_nodes << " " << hidden_nodes << " " << output_nodes << " " << training_rate << " ";

	for (size_t i = 0; i < wih.rows(); i++)
	{
		for (size_t j = 0; j < wih.columns(); j++)
		{
			out << wih(i, j) << " ";
		}
	}

	for (size_t i = 0; i < who.rows(); i++)
	{
		for (size_t j = 0; j < who.columns(); j++)
		{
			out << who(i, j) << " ";
		}
	}

	out.close();
}

void NeuroNet::load()
{
	std::fstream in;
	in.open("./width.txt", std::fstream::in);

	in >> input_nodes >> hidden_nodes >> output_nodes >> training_rate;

	wih = Matrix<double>(hidden_nodes, input_nodes);
	who = Matrix<double>(output_nodes, hidden_nodes);

	for (size_t i = 0; i < wih.rows(); i++)
	{
		for (size_t j = 0; j < wih.columns(); j++)
		{
			double value;
			in >> value;

			wih.insert(i, j, value);
		}
	}

	for (size_t i = 0; i < who.rows(); i++)
	{
		for (size_t j = 0; j < who.columns(); j++)
		{
			double value;
			in >> value;

			who.insert(i, j, value);
		}
	}

	in.close();
}
