#pragma once

#include <vector>

#include "Connection.h"

class Layer;

class Neuron
{
public:
	Neuron();
	~Neuron();

	auto	feedForward(Layer* layer) -> void;
	auto	updateInputWeights(float eta, float alpha, std::vector<Connection>* connections) -> void;
	auto	calcOutputGradients(float targetVal) -> void;
	auto	calcHiddenGradients(Layer& layer) -> void;

	auto	sumDOW(std::vector<Connection>* connections) -> float;

	auto	transferFunctionTanh(float x) -> float { return tanh(x); }
	auto	transferFunctionDerivativeTanh(float x) -> float { return 1.0f - tanh(x) * tanh(x); }

	auto	getOutput() const -> float { return m_output; }
	auto	setOutput(float value) -> void { m_output = value; }

	auto	getGradient() const -> float { return m_gradient; }
	auto	setGradient(float value) -> void { m_gradient = value; }

	std::vector<unsigned int> m_backConnections;
	std::vector<unsigned int> m_forwardConnections;

private:
	// might remove that at some point

	float m_output;
	float m_gradient;


	//std::vector<unsigned int> m_backConnectionsIndices;
	//std::vector<unsigned int> m_forwardConnectionIndices;
};