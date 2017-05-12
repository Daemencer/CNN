#include "Layer.h"

#include "Connection.h"

Layer::Layer(unsigned int neuronCount, ELayerType type)
{
	m_depth = 0.0f;
	m_x = 0.0f;
	m_y = 0.0f;

	m_layerType = type;

	m_backConnectionsCount = 0.0f;

	for (unsigned int i = 0; i < neuronCount; ++i)
	{
		Neuron n;

		// TODO
		// initialize the neuron

		m_neurons.push_back(n);
	}
}


Layer::~Layer()
{

}


auto	Layer::feedForward() -> void
{
	// feedForward all of the neurons on that layer
	for (auto& neuron : m_neurons)
		neuron.feedForward(this);
}


auto	Layer::backPropagation(std::vector<float>& targetVals) -> void
{

}


auto	Layer::calcGradients(const float* targetVals) -> void
{
	if (m_layerType == ELayerType::OUTPUT)
	{
		for (unsigned int i = 0; i < m_neurons.size(); ++i)
		{
			m_neurons[i].calcOutputGradients(targetVals[i]);
		}
	}
	else if (m_layerType == ELayerType::HIDDEN)
	{
		for (unsigned int i = 0; i < m_neurons.size(); ++i)
		{
			m_neurons[i].calcHiddenGradients(*this);
		}
	}
}


auto	Layer::updateWeights(float eta, float alpha) -> void
{
	for (unsigned int i = 0; i < m_neurons.size(); ++i)
	{
		m_neurons[i].updateInputWeights(eta, alpha, m_connections);
	}
}


auto	Layer::Connect(Layer& previousLayer) -> void
{
	// we connect every single one of our neurons
	for (unsigned int myNeuronsCount = 0; myNeuronsCount < m_neurons.size(); ++myNeuronsCount)
	{
		for (unsigned int prevLayerNeuronsCount = 0; prevLayerNeuronsCount < previousLayer.m_neurons.size(); ++prevLayerNeuronsCount)
		{
			Neuron& fromNeuron = previousLayer.m_neurons[prevLayerNeuronsCount];
			Neuron& toNeuron = m_neurons[myNeuronsCount];

			Connection connection(fromNeuron, toNeuron);

			unsigned int connectionIndex = (*m_connections).size();

			fromNeuron.m_forwardConnections.push_back(connectionIndex);
			toNeuron.m_backConnections.push_back(connectionIndex);

			(*m_connections).push_back(connection);
			++m_backConnectionsCount;
		}
	}
}


auto	Layer::ConnectBias(Neuron& bias) -> void
{
	// take the given bias and establish a backConnection with it as fromNeuron to all current Neurons
	// by doing it like this, it won't link to this layer's bias and the output layer doesn't have a bias
	for (unsigned int i = 0; i < m_neurons.size(); ++i)
	{
		Neuron& toNeuron = m_neurons[i];

		Connection connection(bias, toNeuron);

		unsigned int connectionIndex = (*m_connections).size();

		bias.m_forwardConnections.push_back(connectionIndex);
		toNeuron.m_backConnections.push_back(connectionIndex);

		(*m_connections).push_back(connection);
		++m_backConnectionsCount;
	}
}