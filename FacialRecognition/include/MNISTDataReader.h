#pragma once

#include <array>
#include <vector>

struct MNISTNumber
{
	unsigned char number;
	std::array<unsigned char, 255> data;

	MNISTNumber(unsigned char p_number, std::array<unsigned char, 784> p_data)
	{
		number = p_number;
		data = p_data;
	}
};

class MNISTDataReader
{
public:
	MNISTDataReader() = default;
	~MNISTDataReader() = default;

	auto	Read(const char* filename) -> void;

private:
	std::vector<MNISTNumber> m_data;
};