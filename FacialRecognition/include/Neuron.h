#pragma once

#include <cstdlib>
#include <cmath>
#include <vector>

#include "NeuralNet.h"

namespace FacialRecognition
{

struct Connection
{
	double weight;
	double deltaWeight;
};

class Neuron
{
public:
	Neuron(unsigned int outputCount, unsigned int p_layerIndex);

	auto feedForward(const Layer& previousLayer) -> void;

	auto calculateOutputGradients(double targetVal) -> void;

	auto calculateHiddenGradients(const Layer& nextLayer) -> void;

	auto updateInputWeights(Layer& previousLayer) -> void;

	auto getOutputValue() const -> double { return m_outputValue; }
	auto setOutputValue(double value) -> void { m_outputValue = value; }

	auto getGradient() const -> double { return m_gradient; }

	auto getConnections() const -> const std::vector<Connection>& { return m_connections; }

private:
	static auto activationFunction(double x) -> double { return tanh(x); }
	static auto activationFunctionDerivative(double x) -> double { return 1.0 - x * x;}

	static auto randomWeight() -> double { return rand() / double(RAND_MAX); }


	static double eta;
	static double alpha;


	auto sumDOW(const Layer& nextLayer) const -> double;


	unsigned int m_layerIndex;
	std::vector<Connection> m_connections;

	double m_outputValue = 0;
	double m_gradient = 0;
};

}