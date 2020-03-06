#pragma once

#include "Matrix.h"
#include <vector>

class NeuroNet
{
public: 
	explicit NeuroNet();
	explicit NeuroNet(int input_nodes, int hidden_layers, int output_nodes, double training_rate);

	std::vector<double> query(std::vector<double>& input_values);

	void train(std::vector<double>& input_values, std::vector<double>& target_values);

	void save();
	void load();

private:
	Matrix<double> wih;
	Matrix<double> who;

	Matrix<double> wih_buffer;
	Matrix<double> who_buffer;
	
	double training_rate;

	int input_nodes;
	int hidden_nodes;
	int output_nodes;
};

