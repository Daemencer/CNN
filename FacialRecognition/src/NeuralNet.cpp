#include "NeuralNet.h"

#include <cassert>

#include "Neuron.h"
#include "Layer.h"

auto	NeuralNet::FeedForward(std::vector<double> inputs, unsigned int inCount, double* outputs, unsigned int outCount) -> void
{
// make sure we have as many input values as there are neurons in the first layer
assert(inCount == m_layers[0]->GetNeurons().size());

// plug the input into the first layer
for (unsigned int i = 0; i < m_layers[0]->GetNeurons().size(); ++i)
{
	m_layers[0]->GetNeurons()[i]->SetOutput(inputs[i]);
}

// then feed forward all the other layers
for (unsigned int i = 1; i < m_layers.size(); ++i)
{
	m_layers[i]->FeedForward();
}

// load up the results in the output vector
if (outputs != nullptr)
{
	Layer* l = *(m_layers.end() - 1);

	for (unsigned int i = 0; i < outCount; ++i)
	{
		outputs[i] = l->GetNeurons()[i]->GetOutput();
	}
}
}


//auto	NeuralNet::BackPropagation(double* outputs, double* expectedOutputs, double count) -> void
//{
//	Layer* lastLayer = *(m_layers.end() - 1);
//
//	int layerCount = m_layers.size();
//
//	std::vector<double> last_frame_error(lastLayer->GetNeurons().size());
//	std::vector<std::vector<double>> differentials;
//
//	for (unsigned int i = 0; i < lastLayer->GetNeurons().size(); ++i)
//	{
//		last_frame_error[i] = outputs[i] - expectedOutputs[i];
//	}
//
//	// already fill the last one
//	differentials[layerCount - 1] = last_frame_error;
//
//	// allocate stuff
//	for (unsigned int i = 0; i < layerCount - 1; ++i)
//	{
//		differentials[i].resize(m_layers[i]->GetNeurons().size());
//	}
//
//	// back prop through every layer but the first one
//	for (unsigned int i = layerCount - 1; i > 1; ++i)
//	{
//		m_layers[i]->BackPropagate(differentials[i], differentials[i - 1], m_etaLearningRate);
//	}
//
//	differentials.clear();
//}


auto	NeuralNet::BackPropagation(std::vector<double>& targetValues) -> void
{
	// calculate overall net error (RMS of output error)
	Layer* outputLayer = m_layers.back();
	m_error = 0.0;

	for (unsigned int n = 0; n < outputLayer->GetNeurons().size() - 1; ++n)
	{
		double delta = targetValues[n] - outputLayer->GetNeurons()[n]->GetOutput();
		m_error += delta * delta;
	}

	m_error /= outputLayer->GetNeurons().size() - 1;
	m_error = sqrt(m_error);

	// Implement a recent average measurement
	m_recentAverageError = (m_recentAverageError * m_recentAverageSmoothingFactor + m_error) /
		(m_recentAverageSmoothingFactor + 1.0);

	// Calculate output layer gradients
	for (unsigned int i = 0; i < outputLayer->GetNeurons().size() - 1; ++i)
	{
		double nOutput = outputLayer->GetNeurons()[i]->GetOutput();

		m_gradient = (targetValues[i] - nOutput) * Neuron::DSIGMOID(nOutput);
	}

	// Calculate gradients on hidden layers
	for (unsigned int layerNum = m_layers.size() - 2; layerNum > 0; --layerNum)
	{
		Layer* hiddenLayer = m_layers[layerNum];
		Layer* nextLayer = m_layers[layerNum + 1];

		for (unsigned int n = 0; n < hiddenLayer->GetNeurons().size(); ++n)
		{
			double sum = 0.0f;

			for (unsigned int i = 0; i < nextLayer->GetNeurons().size() - 1; ++i)
			{
				Neuron* currentNeuron = hiddenLayer->GetNeurons()[i];

				//sum += currentNeuron->GetConnections()[i]->GetNeuronIndex()
			}

			/*
			double sum = 0.0f;

			// Sum of the contributions of the errors at the nodes we feed

			for (unsigned int n = 0; n < nextLayer.size() - 1; ++n)
			{
				sum += m_connections[n].weight * nextLayer[n].m_gradient;
			}

			return sum;

			double dow = sumDOW(nextLayer);
			m_gradient = dow * Neuron::activationFunctionDerivative(m_outputValue);
			*/



			//hiddenLayer[n].calculateHiddenGradients(nextLayer);
		}
	}

	// For all layers from output to first hidden layer,
	// update connection weights
	for (unsigned int layerNum = m_layers.size() - 1; layerNum > 0; --layerNum)
	{
		//Layer& layer = m_layers[layerNum];
		//Layer& previousLayer = m_layers[layerNum - 1];

		//for (unsigned int n = 0; n < layer.size() - 1; ++n)
		//{
		//	layer[n].updateInputWeights(previousLayer);
		//}
	}
}