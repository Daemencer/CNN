#pragma once

#include <fstream>

class DataReader
{
public:
	DataReader(const char* filename)
	{
		file.open(filename);
	}

	~DataReader()
	{
		file.close();
	}

	std::ifstream file;
};