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
	for (unsigned int i = 0; i < m_backConnections.size(); ++i)
	{
		int idx = m_backConnections[i];
		Connection& connection = (*connections)[idx];

		const Neuron& fromNeuron = connection.m_fromNeuron;
		float oldDeltaWeight = connection.m_deltaWeight;

		float newDeltaWeigth = 
			// Individual input, magnified by the gradient and train rate:
			eta
			* fromNeuron.m_output
			* m_gradient
			// Add momentum = a fraction of the previous delta weight;
			+ alpha
			* oldDeltaWeight;

		connection.m_deltaWeight = newDeltaWeigth;
		connection.m_weight += newDeltaWeigth;
	}
}


auto	Neuron::calcOutputGradients(float targetVal) -> void
{
	float delta = targetVal - m_output;
	m_gradient = delta * transferFunctionDerivativeTanh(m_output);
}


auto	Neuron::calcHiddenGradients(Layer& layer) -> void
{
	float dow = sumDOW(layer.m_connections);
	m_gradient = dow * transferFunctionDerivativeTanh(m_output);
}


auto	Neuron::sumDOW(std::vector<Connection>* connections) -> float
{
	float sum = 0.0f;

	for (unsigned int i = 0; i < m_forwardConnections.size(); ++i)
	{
		int idx = m_forwardConnections[i];
		const Connection& connection = (*connections)[idx];

		sum += connection.m_weight * connection.m_toNeuron.m_gradient;
	}

	return sum;
}