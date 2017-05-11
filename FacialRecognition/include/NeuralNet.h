#pragma once

#include <vector>

class Layer;

class NeuralNet
{
public:
	NeuralNet() = default;
	~NeuralNet() = default;

	auto	FeedForward(std::vector<double> inputs, unsigned int inCount, double* outputs, unsigned int outCount) -> void;

	auto	BackPropagation(std::vector<double>& targetValues) -> void;

private:
	double m_error;
	double m_recentAverageError;
	double m_recentAverageSmoothingFactor;

	double m_gradient;

	double m_etaLearningRate;

	std::vector<Layer*> m_layers;
};