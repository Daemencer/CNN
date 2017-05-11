#pragma once

class Weight
{
public:
	Weight();
	~Weight();

	auto	GetValue() const -> double { return m_value; }

private:
	double m_value;
};