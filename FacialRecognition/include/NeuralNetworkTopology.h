#pragma once

#include <vector>

namespace FacialRecognition
{

struct NeuralNetworkTopology
{
public:
	NeuralNetworkTopology() { }
	NeuralNetworkTopology(const std::vector<unsigned int>& p_data) { data = p_data; }
	~NeuralNetworkTopology() { data.clear(); }

	std::vector<unsigned int> data;
};

typedef NeuralNetworkTopology NNTopology;

}