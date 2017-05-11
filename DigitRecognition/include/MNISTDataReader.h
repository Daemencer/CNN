#pragma once

#define PIXEL_PER_IMAGE 784

#include <array>
#include <vector>

#include "DataReader.h"

struct MNISTNumber
{
	unsigned int number;
	std::array<float, 10> output;
	std::array<float, PIXEL_PER_IMAGE> pixels;

	MNISTNumber(unsigned int p_number, std::array<float, PIXEL_PER_IMAGE> p_pixels)
	{
		number = p_number;
		pixels = p_pixels;

		// create the array of output for the net
		_CreateOutput(p_number);
	}

private:
	auto	_CreateOutput(unsigned int number) -> void;
};

class MNISTDataReader:
	public DataReader
{
public:
	MNISTDataReader(const char* filename);
	~MNISTDataReader();

	auto	GenerateData() -> void;

	//auto	Shuffle() -> void;


	std::vector<MNISTNumber>	m_images;

};