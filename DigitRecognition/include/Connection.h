#pragma once

class Neuron;

class Connection
{
public:
	Connection(Neuron& fromNeuron, Neuron& toNeuron);
	~Connection() = default;

	float	m_weight;
	float	m_deltaWeight;

	Neuron&	m_fromNeuron;
	Neuron& m_toNeuron;
};