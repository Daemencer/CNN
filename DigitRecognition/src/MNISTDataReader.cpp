#include "MNISTDataReader.h"

#include <fstream>
#include <sstream>


MNISTDataReader::MNISTDataReader(const char* filename):
	DataReader(filename)
{
}


MNISTDataReader::~MNISTDataReader()
{
}


auto	MNISTDataReader::GenerateData() -> void
{
	// ignore the first line
	std::string line;
	std::getline(file, line);

	// process the rest of the lines
	while (std::getline(file, line))
	{
		unsigned int index = 0;

		std::array<float, PIXEL_PER_IMAGE> image;

		std::istringstream iss(line);
		std::string token;

		// get the value of the drawn number, first digit in the line
		std::getline(iss, token, ',');
		//unsigned int number = *(reinterpret_cast<const unsigned int *> (token.c_str()));
		unsigned int number = std::stoul(token);

		// get the 784 pixels values
		while (std::getline(iss, token, ','))
		{
			//image[index] = *(reinterpret_cast<const float *> (token.c_str()));
			image[index] = std::stof(token);
			++index;
		}

		MNISTNumber mNumber(number, image);
		m_images.push_back(mNumber);

		index = 0;
	}
}


auto	MNISTNumber::_CreateOutput(unsigned int number) -> void
{
	for (unsigned int i = 0; i < 10; ++i)
	{
		if (i == number)
			output[i] = 1.0f;
		else
			output[i] = 0.0f;
	}
}