#pragma once

#include <fstream>
#include <vector>

namespace FacialRecognition
{

class Neuron;
class TrainingData;

typedef std::vector<Neuron> Layer;

class NeuralNet
{
public:
	NeuralNet(const std::vector<unsigned int>& topology);
	~NeuralNet();

	auto train(const TrainingData& trainingData, unsigned int iterations) -> void;

	auto feedForward(const std::vector<double>& inputVals) -> void;

	auto backProp(const std::vector<double>& targetVals) -> void;
	
	auto getResults(std::vector<double>& resultVals) const -> void;

	auto getRecentAverageError() const -> double { return m_recentAverageError; }

private:
	std::vector<Layer> m_layers;
	double m_error;

	double m_recentAverageError = 0;
	double m_recentAverageSmoothingFactor = 0;

	// tmp debug
	std::ofstream file;
	std::ofstream ostream;
};

}