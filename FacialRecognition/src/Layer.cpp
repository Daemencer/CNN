#include "Layer.h"

#include <cassert>

#include "Neuron.h"
#include "Weight.h"


auto	Layer::FeedForward() -> void
{
	assert(m_previousLayer != nullptr);

	double sum = 0;

	// for each neuron in the layer
	for each (Neuron* n in m_neurons)
	{
		// for each connection of the current neuron
		// todo: take the bias into account properly
		for each (Connection* c in n->GetConnections())
		{
			// add to the sum the value of the outpout from the previous layer multiplied by its weight
			sum += m_previousLayer->m_neurons[c->GetNeuronIndex()]->GetOutput() * m_weights[c->GetWeightIndex()]->GetValue();
		}

		// TODO sigmoid function
		n->SetOutput(Neuron::SIGMOID(sum));
	}
}


auto	Layer::BackPropagate(std::vector<double>& inError, std::vector<double>& outError, double etaLearningRate) -> void
{
	for (unsigned int i = 0; i < m_neurons.size(); ++i)
	{
		double output = m_neurons[i]->GetOutput();
		//inError[i] = Neuron::DSIGMOID(output) * 
	}
}