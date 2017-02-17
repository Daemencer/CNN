#include "Neuron.h"

namespace FacialRecognition
{

double Neuron::eta = 0.05;
double Neuron::alpha = 0.001;

Neuron::Neuron(unsigned int outputCount, unsigned int p_layerIndex)
{
	for (unsigned int i = 0; i < outputCount; ++i)
	{
		m_connections.push_back(Connection());
		m_connections.back().weight = randomWeight();
	}

	m_layerIndex = p_layerIndex;
}


auto Neuron::feedForward(const Layer& previousLayer) -> void
{
	double sum = 0.0;

	for (unsigned int i = 0; i < previousLayer.size(); ++i)
	{
		sum += previousLayer[i].getOutputValue() *
				previousLayer[i].m_connections[m_layerIndex].weight;
	}

	m_outputValue = Neuron::activationFunction(sum);
}


auto Neuron::calculateOutputGradients(double targetVal) -> void
{
	double delta = targetVal - m_outputValue;
	m_gradient = delta * Neuron::activationFunctionDerivative(m_outputValue);
}


auto Neuron::calculateHiddenGradients(const Layer& nextLayer) -> void
{
	double dow = sumDOW(nextLayer);
	m_gradient = dow * Neuron::activationFunctionDerivative(m_outputValue);
}


auto Neuron::updateInputWeights(Layer& previousLayer) -> void
{
	// The weights to be updated are in the connection container
	// in the neurons in the preceding layer

	for (unsigned int n = 0; n < previousLayer.size(); ++n)
	{
		Neuron& neuron = previousLayer[n];
		double oldDeltaWeight = neuron.m_connections[m_layerIndex].deltaWeight;
		double newDeltaWeight = 
			// individual input, magnified by the gradient and train rate:
			eta
			* neuron.getOutputValue()
			* m_gradient
			// also add momentum = a fraction of the previous delta weight
			+ alpha
			* oldDeltaWeight;

		neuron.m_connections[m_layerIndex].deltaWeight = newDeltaWeight;
		neuron.m_connections[m_layerIndex].weight += newDeltaWeight;

	}
}


auto Neuron::sumDOW(const Layer& nextLayer) const -> double
{
	double sum = 0.0f;

	// Sum of the contributions of the errors at the nodes we feed

	for (unsigned int n = 0; n < nextLayer.size() - 1; ++n)
	{
		sum += m_connections[n].weight * nextLayer[n].m_gradient;
	}

	return sum;
}

}