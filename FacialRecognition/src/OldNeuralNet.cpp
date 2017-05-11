#include "OldNeuralNet.h"

#include <iostream>
#include <cassert>

#include "OldNeuron.h"
#include "IrisTrainingData.h"
#include "Utils.h"

namespace FacialRecognition
{

OldNeuralNet::OldNeuralNet(const std::vector<unsigned int>& topology)
{
	unsigned int layerCount = topology.size();
	for (unsigned int layerNum = 0; layerNum < layerCount; ++layerNum)
	{
		m_layers.push_back(OldLayer());

		unsigned int outputCount = (layerNum == topology.size() - 1) ? 0 : topology[layerNum + 1];

		// fill the layer with neurons
		// and add a bias neuron
		for (unsigned int neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum)
		{
			m_layers.back().push_back(Neuron(outputCount, neuronNum));
			//std::cout << "Created a Neuron!" << std::endl;
		}

		// Force the bias output value to 1.0
		m_layers.back().back().setOutputValue(1.0);
	}

	file.open("resources/neural_network_data_evolution.txt");
	ostream.open("resources/iris_results.txt");
}


OldNeuralNet::~OldNeuralNet()
{
	file.close();
	ostream.close();
}


auto OldNeuralNet::train(const TrainingData& trainingData, unsigned int iterations) -> void
{
	// do the epochs to train the network
	for (unsigned int i = 0; i < iterations; ++i)
	{
		std::vector<double> resultVals;
		int trainingPass = 0;

		// keep going for as long as there are samples in the array
		while (trainingPass < trainingData.getInputValues().size())
		{
			//ostream << std::endl << "Pass " << trainingPass;

			//Utils::printVector(": Inputs:", trainingData.getInputValues(trainingPass), ostream);
			feedForward(trainingData.getInputValues(trainingPass));

			// collect the neural net's actual results
			getResults(resultVals);
			//Utils::printVector("Outputs:", resultVals, ostream);

			// Train the neural net on what the output should have been
			//Utils::printVector("Targets:", trainingData.getTargetValues(trainingPass), ostream);
			backProp(trainingData.getTargetValues(trainingPass));

			//ostream << "Net recent average error: " << getRecentAverageError() << std::endl;

			++trainingPass;
		}

		//ostream << std::endl << "Done" << std::endl;

		//std::cout << "Finishing an epoch" << std::endl;
	}
}


auto OldNeuralNet::feedForward(const std::vector<double>& inputVals) -> void
{
	assert(inputVals.size() == (m_layers[0].size() - 1));

	// assign the input values to each neuron
	for (unsigned int i = 0; i < inputVals.size(); ++i)
	{
		m_layers[0][i].setOutputValue(inputVals[i]);
	}

	// forward propagation
	for (unsigned int i = 1; i < m_layers.size(); ++i)
	{
		OldLayer& previousLayer = m_layers[i - 1];

		for (unsigned int j = 0; j < m_layers[i].size() - 1; ++j)
		{
			m_layers[i][j].feedForward(previousLayer);
		}
	}


	//// DEBUG PRINTING
	//file << "Neural Network: {" << std::endl;
	//for (unsigned int i = 0; i < m_layers.size(); ++i)
	//{
	//	Layer& l = m_layers[i];

	//	file << "\tLayer[" << i << "] : { " << std::endl;

	//	for (unsigned int j = 0; j < m_layers[i].size(); ++j)
	//	{
	//		Neuron& n = l[j];

	//		file << "\t\tNeuron[" << j << "] : { " << "output: " << n.getOutputValue() << ", gradient: " << n.getGradient() << ", weights: {";

	//		if (n.getConnections().size() == 0) file << " }" << std::endl;
	//		else file << std::endl;

	//		for (unsigned int k = 0; k < n.getConnections().size(); ++k)
	//		{
	//			if (k == (n.getConnections().size() - 1))
	//				file << "\t\t\t" << n.getConnections()[k].weight << " }" << std::endl;
	//			else
	//				file << "\t\t\t" << n.getConnections()[k].weight << std::endl;
	//		}
	//	}
	//}

	//file << " }" << std::endl << std::endl;
}


auto OldNeuralNet::backProp(const std::vector<double>& targetVals) -> void
{
	// calculate overall net error (RMS of output error)
	OldLayer& outputLayer = m_layers.back();
	m_error = 0.0;

	for (unsigned int n = 0; n < outputLayer.size() - 1; ++n)
	{
		double delta = targetVals[n] - outputLayer[n].getOutputValue();
		m_error += delta * delta;
	}

	m_error /= outputLayer.size() - 1;
	m_error = sqrt(m_error);

	// Implement a recent average measurement
	m_recentAverageError = (m_recentAverageError * m_recentAverageSmoothingFactor + m_error) /
							(m_recentAverageSmoothingFactor + 1.0);

	// Calculate output layer gradients
	for (unsigned int n = 0; n < outputLayer.size() - 1; ++n)
	{
		outputLayer[n].calculateOutputGradients(targetVals[n]);
	}

	// Calculate gradients on hidden layers
	for (unsigned int layerNum = m_layers.size() - 2; layerNum > 0; --layerNum)
	{
		OldLayer& hiddenLayer = m_layers[layerNum];
		OldLayer& nextLayer = m_layers[layerNum + 1];

		for (unsigned int n = 0; n < hiddenLayer.size(); ++n)
		{
			hiddenLayer[n].calculateHiddenGradients(nextLayer);
		}
	}

	// For all layers from output to first hidden layer,
	// update connection weights
	for (unsigned int layerNum = m_layers.size() - 1; layerNum > 0; --layerNum)
	{
		OldLayer& layer = m_layers[layerNum];
		OldLayer& previousLayer = m_layers[layerNum - 1];

		for (unsigned int n = 0; n < layer.size() - 1; ++n)
		{
			layer[n].updateInputWeights(previousLayer);
		}
	}
}


auto OldNeuralNet::getResults(std::vector<double>& resultVals) const -> void
{
	resultVals.clear();

	for (unsigned int n = 0; n < m_layers.back().size() - 1; ++n)
	{
		resultVals.push_back(m_layers.back()[n].getOutputValue());
	}
}


}