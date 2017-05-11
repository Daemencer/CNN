#include "Neuron.h"

#include "Layer.h"
#include "Connection.h"

Neuron::Neuron()
{
	m_output = 0.0f;
	m_gradient = 0.0f;
}


Neuron::~Neuron()
{
}


auto	Neuron::feedForward(Layer* layer) -> void
{
	float sum = 0.0f;

	for (unsigned int i = 0; i < m_backConnections.size(); ++i)
	{
		// get the connection index from the backConnections array
		unsigned int idx = m_backConnections[i];
		// get the actual connection using the index
		const Connection& connection = (*layer->m_connections)[idx];
		// add the weighted output to the sum
		sum += connection.m_fromNeuron.getOutput() * connection.m_weight;
	}

	setOutput(transferFunctionTanh(sum));
}


auto	Neuron::updateInputWeights(float eta, float alpha, std::vector<Connection>* connections) -> void
{

}


auto	Neuron::calcOutputGradients(float targetVal) -> void
{

}


auto	Neuron::calcHiddenGradients(Layer& layer) -> void
{

}