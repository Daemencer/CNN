#pragma once

/*
	This class will simply describe a neural network's topology
	For now we only have simple layer with no depth. 
	No convolution or pooling layers either.
	We only describe how many layers and how many neurons in each of them.
	We connect everything to everything for now.
*/

#include <vector>

struct Topology
{
	std::vector<unsigned int> m_layers;
};