#pragma once

#include "Neuron.h"
#include "matrix.h"

class NeuroNet
{
public: 
	explicit NeuroNet(int input_nodes, int hidden_layers, int output_nodes, double training_rate);

	std::vector<double> query(std::vector<double>& input_values);

	void train(std::vector<double>& input_values, std::vector<double>& target_values);

private:
	Matrix<double> wih;
	Matrix<double> who;
	
	double training_rate;

	int input_nodes;
	int hidden_nodes;
	int output_nodes;
};

