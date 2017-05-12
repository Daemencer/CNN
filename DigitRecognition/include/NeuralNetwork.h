#pragma once

#include <vector>

#include "Connection.h"
#include "Neuron.h"

// tmp
#include "MNISTDataReader.h"

class Layer;
class Topology;

class NeuralNetwork
{
public:
	NeuralNetwork();
	~NeuralNetwork();

	auto	initialize(Topology& topology) -> void;

	//auto	feedForward(std::vector<float>& inputVals) -> void;
	auto	feedForward(MNISTNumber sample) -> void;	// temporary
	//auto	backProp(std::vector<float>& outputVals) -> void;	// temporary
	auto	backPropagation(const MNISTNumber& sample) -> void;	// temporary

	auto	calculateOverallNetError(const std::vector<float>& targetVals) -> void;

	auto	adjustEta() -> float;

	Neuron	m_bias;

private:
	std::vector<Layer*> m_layers;

	float m_eta;
	float m_alpha;

	float m_error;
	float m_recentAverageError;
	float m_recentAverageSmoothingFactor;
	float m_lastRecentAverageError;

	// TODO: don't know yet if this will stay
	// this guy will probably be responsible for the Connections life
	std::vector<Connection> m_connections;
};

using NNet = NeuralNetwork;