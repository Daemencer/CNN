#include "NeuralNetwork.h"

#include <algorithm>

#include "Layer.h"
#include "Topology.h"

NeuralNetwork::NeuralNetwork()
{
	m_eta = 0.01f;
	m_alpha = 0.1f;
	m_error = 1.0f;
	m_recentAverageError = 1.0f;
	m_lastRecentAverageError = 1.0f;
	m_recentAverageSmoothingFactor = 125.0f;
}


NeuralNetwork::~NeuralNetwork()
{

}


auto	NeuralNetwork::initialize(Topology& topology) -> void
{
	// create all the layers
	for (unsigned int i = 0; i < topology.m_layers.size(); ++i)
	{
		Layer* layer = new Layer(topology.m_layers[i]);
		layer->m_connections = &m_connections;
		m_layers.push_back(layer);
	}

	// fully connect layers properly
	for (unsigned int i = 1; i < topology.m_layers.size(); ++i)
	{
		Layer* prevLayer = m_layers[i - 1];
		Layer* currentLayer = m_layers[i];

		currentLayer->Connect(*prevLayer);
	}

	// some layers need a bias neuron
	for (unsigned int i = 1; i < topology.m_layers.size(); ++i)
	{
		m_layers[i]->ConnectBias(m_bias);
	}
}


//auto	NeuralNetwork::feedForward(std::vector<float>& inputVals) -> void
auto	NeuralNetwork::feedForward(MNISTNumber sample) -> void
{
	Layer& inputLayer = *m_layers[0];

	// plug the input values to the first layer's outputs
	for (unsigned int i = 0; i < inputLayer.GetNeurons().size(); ++i)
	{
		inputLayer.GetNeuron(i).setOutput((float)sample.pixels[i]);
	}

	// feedforward on the rest of the layers
	std::for_each(m_layers.begin() + 1, m_layers.end(), [](Layer* layer) {
		layer->feedForward();
	});

	// tmp horrible
	// need to rework data integrity by ... the samples into a class
	std::vector<float> outputVals;
	for (unsigned int i = 0; i < 10; ++i)
	{
		outputVals.push_back((float)sample.output[i]);
	}

	// TODO
	// calculate overall net error
	calculateOverallNetError(outputVals);
}


auto	NeuralNetwork::backPropagation(std::vector<float>& targetVals) -> void
{

}


auto	NeuralNetwork::calculateOverallNetError(const std::vector<float>& targetVals) -> void
{
	m_error = 0.0f;
		
	const Layer& outputLayer = *m_layers.back();

	// magic error calculation
	// for all the output neurons, compare the output to the expected output and do a delta of the error
	// the error is then delta * delta
	// at the end of it all, divide by twice the amount of neurons on the output layer
	for (unsigned int i = 0; i < outputLayer.m_neurons.size(); ++i)
	{
		float delta = targetVals[i] - outputLayer.m_neurons[i].getOutput();
		m_error += delta * delta;
	}
	m_error /= 2.0f * outputLayer.m_neurons.size();

	// save the recent average error of the last epoch for comparisons
	m_lastRecentAverageError = m_recentAverageError;

	// recalculate the new recent average error
	m_recentAverageError = (m_recentAverageError * m_recentAverageSmoothingFactor + m_error) / (m_recentAverageSmoothingFactor + 1.0f);


}