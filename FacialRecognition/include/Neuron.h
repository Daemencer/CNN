#pragma once

#include <vector>
#include <cmath>

#include "Connection.h"

class Neuron
{
public:
	Neuron();
	~Neuron();

	static	auto	SIGMOID(double x) -> double { return tanh(x); }
	static	auto	DSIGMOID(double x) -> double { return 1.0 - x * x;
	}

	auto	AddConnection(Connection* connection) -> void;

	auto	GetOutput() const -> double { return m_output; }
	auto	SetOutput(double output) -> void { m_output = output; }

	auto	GetConnections() const -> const std::vector<Connection*>& { return m_connections; }

private:
	double m_output;

	std::vector<Connection*> m_connections;
};