#include "Neuron.h"

auto	Neuron::AddConnection(Connection* connection) -> void
{
	// TODO
	// could do a verification
	m_connections.push_back(connection);
}