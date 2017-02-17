#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "NeuralNetworkTopology.h"

namespace FacialRecognition
{

typedef std::vector<double> Sample;

class TrainingData
{
public:
	TrainingData() { }
	~TrainingData() {}

	auto	getTopology() const -> NNTopology { return m_topology; }

	auto	getInputValues() const -> const std::vector<Sample>& { return m_inputValues; }
	auto	getInputValues(int index) const -> const Sample& { return m_inputValues[index]; }

	auto	getTargetValues() const -> const std::vector<Sample>& { return m_targetValues; }
	auto	getTargetValues(int index) const -> const Sample& { return m_targetValues[index]; }

	//auto	setTopology(const NNTopology& p_topology) -> void { m_topology = p_topology; }
	//auto	setInputValues(const std::vector<double>& p_inputValues) -> void { m_inputValues = p_inputValues; }
	//auto	setTargetValues(const std::vector<double>& p_targetValues) -> void { m_targetValues = p_targetValues; }

protected:
	NNTopology m_topology;

	std::vector<Sample>	m_inputValues;
	std::vector<Sample> m_targetValues;
	std::vector<Sample> m_resultValues;
};

}