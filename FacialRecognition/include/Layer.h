#pragma once

#include <vector>

class Neuron;
class Weight;

class Layer
{
public:
	Layer();
	~Layer();

	auto	FeedForward() -> void;

	auto	BackPropagate(std::vector<double>& inError, std::vector<double>& outError, double etaLearningRate) -> void;

	auto	GetPreviousLayer() const -> Layer const* { return m_previousLayer; }

	auto	GetNeurons() const -> const std::vector<Neuron*>& { return m_neurons; }
	auto	GetWeights() const -> const std::vector<Weight*>& { return m_weights; }

private:
	Layer*	m_previousLayer;

	std::vector<Neuron*>	m_neurons;
	std::vector<Weight*>	m_weights;
};