#include <iostream>

#include "MNISTDataReader.h"

#include "NeuralNetwork.h"
#include "Topology.h"

int main(int ac, char** av)
{
	// read the input file for training data
	MNISTDataReader reader("resources/dataset/train_full.csv");
	reader.GenerateData();

	//// open an output stream to the weights

	//// using topology file
	Topology topology;
	topology.m_layers.push_back(784);
	topology.m_layers.push_back(1000);
	topology.m_layers.push_back(10);

	// create a neural net
	NNet net;
	net.initialize(topology);

	//// iniitalize it to the saved weights

	// train it a given amount of times
	//// train a certain amount of times depending on recentAverageError and an error threshhold
	bool train = true;

	int epochCount = 0;

	while (train)
	{
		int index = epochCount % reader.m_images.size();
		MNISTNumber sample = reader.m_images[index];

		// feedforward the input train data
		net.feedForward(sample);

		// backprop the net to calculate net error
		net.backPropagation(sample);

		if (++epochCount > 100000) train = false;
	}

	//// save weights

	// return

	return 0;
}