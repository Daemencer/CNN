#pragma once

#include <vector>

#include "Neuron.h"
#include "Connection.h"

class Layer
{
public:
	Layer(unsigned int neuronCount); // TODO: add a topology at some point
	~Layer();

	auto	feedForward() -> void;
	auto	backPropagation(std::vector<float>& targetVals) -> void;
	auto	updateWeights(float eta, float alpha) -> void;


	auto	Connect(Layer& layer) -> void;

	auto	ConnectBias(Neuron& bias) -> void;

	auto	GetNeurons() const -> const std::vector<Neuron>& { return m_neurons; }

	auto	GetNeuron(unsigned int index) -> Neuron& { return m_neurons[index]; }

	std::vector<Neuron> m_neurons;

	// not sure I'll keep this shit
	std::vector<Connection>*	m_connections;
	unsigned int				m_backConnectionsCount;

private:
	// these 3 could be grouped into a struct
	// fully connected layer default depth = 1, y = 1
	float m_depth;
	float m_x;
	float m_y;
};