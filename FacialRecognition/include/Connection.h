#pragma once

class Connection
{
public:
	Connection();
	~Connection();

	auto	GetNeuronIndex() const -> unsigned int { return m_neuronIndex; }
	auto	GetWeightIndex() const -> unsigned int { return m_weightIndex; }

private:
	unsigned int m_neuronIndex;
	unsigned int m_weightIndex;
};