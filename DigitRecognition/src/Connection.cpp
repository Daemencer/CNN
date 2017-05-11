#include "Connection.h"

#include <cmath>

Connection::Connection(Neuron& fromNeuron, Neuron& toNeuron):
	m_fromNeuron(fromNeuron),
	m_toNeuron(toNeuron)
{
	float random = (float)std::rand();
	float rand_max = (float)RAND_MAX;
	float div = random / rand_max;

	m_weight = div - 0.5f; // between -0.5 and 0.5
	m_deltaWeight = 0.0f;
}