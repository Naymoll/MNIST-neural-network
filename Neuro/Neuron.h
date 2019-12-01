#pragma once

class Connections;

class Neuron
{
public:
	enum Type
	{
		Input = 0,
		Hidden = 1,
		Output = 2,
	};

	Neuron();
	explicit Neuron(float input_value);
	explicit Neuron(Type type);
	~Neuron();
	
	void activate();

	float input_value();
	void set_input_value(float value);

	float output_value();

	Type type();
	void set_type(Type type);

	void add_output_connection(Neuron* neuron, float width);
	void erase_output_connection(Neuron* neuron);

	bool operator ==(const Neuron& other) const;

private:
	void process();

	void add_input_connection(Neuron* neuron);
	void erase_input_connection(Neuron* neuron);

	float m_in_value;
	float m_out_value;
	Type m_type;

	Connections* m_connections;
};

