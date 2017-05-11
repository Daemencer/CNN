#include "MNISTDataReader.h"

#include <fstream>
#include <sstream>
#include <ios>

auto	MNISTDataReader::GenerateData() -> void
{
	std::ifstream input(filename, std::ios::in);

	// ignore the first line
	std::string line;
	std::getline(input, line);

	while (std::getline(input, line))
	{
		unsigned int index = 0;

		std::array<unsigned char, 784> image;

		std::istringstream iss(line);
		std::string token;


		// get the value of the drawn number
		std::getline(iss, token, ',');
		unsigned char number = *(reinterpret_cast<const unsigned char *> (token.c_str()));

		while (std::getline(iss, token, ','))
		{
			image[index] = *(reinterpret_cast<const unsigned char *> (token.c_str()));
			printf("[%d]: %d\n", index, (int)image[index]);
			++index;
		}

		MNISTNumber mNumber(number, image);
		m_data.push_back(mNumber);

		index = 0;
	}

	input.close();
}