#include "Neuron.h"
#include "Connection.h"

Neuron::Neuron()
{
	m_type = Type::Input;
	m_in_value = 0.0f;
	m_out_value = 0.0f;

	m_connections = new Connections();
}

Neuron::Neuron(float input_value)
{
	m_type = Type::Input;
	m_in_value = input_value;
	m_out_value = input_value;

	m_connections = new Connections();
}

Neuron::Neuron(Type type)
{
	m_type = type;
	m_in_value = 0.0f;
	m_out_value = 0.0f;

	m_connections = new Connections();
}

Neuron::~Neuron()
{
	delete m_connections;
}

void Neuron::activate()
{
	if (m_type = Neuron::Input)
		m_out_value = m_in_value;
	else
		process();
}

float Neuron::input_value()
{
	return m_in_value;
}

void Neuron::set_input_value(float value)
{
	m_in_value = value;
}

float Neuron::output_value()
{
	return m_out_value;
}

Neuron::Type Neuron::type()
{
	return m_type;
}

void Neuron::set_type(Type type)
{
	m_type = type;
}

void Neuron::add_input_connection(Neuron* neuron)
{
	m_connections->add_input_connection(neuron);
}

void Neuron::erase_input_connection(Neuron* neuron)
{
	m_connections->erase_input_connection(neuron);
	neuron->erase_output_connection(this);
}

void Neuron::add_output_connection(Neuron* neuron, float width)
{
	m_connections->add_output_connection(neuron, width);
	neuron->add_input_connection(this);
}

void Neuron::erase_output_connection(Neuron* neuron)
{
	m_connections->erase_output_connection(neuron);
	neuron->erase_input_connection(this);
}

bool Neuron::operator==(const Neuron& other) const
{
	return (m_in_value == other.m_in_value &&
			m_out_value == other.m_out_value &&
			m_type == other.m_type &&
			m_connections == other.m_connections);
}

void Neuron::process()
{
	std::vector<Neuron*> input_connections = m_connections->input_connections();

	if (input_connections.empty())
		return;

	for (Neuron *var : input_connections)
	{
		m_in_value += var->m_out_value * var->m_connections->connection_width(this);
	}

	m_out_value = 1 / (1 + exp(-m_in_value));
}