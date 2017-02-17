#include "IrisTrainingData.h"

#include <fstream>
#include <sstream>
#include <string>

namespace FacialRecognition
{

IrisTrainingData::IrisTrainingData(const std::string& filename) :
	TrainingData()
{
	std::ifstream file;
	file.open(filename);

	int pass = 0;

	// initialzes the topology
	m_topology.data = { 4, 5, 3 };

	// fill up the input and target values
	while (!file.eof())
	{
		// get a line
		std::string line;
		getline(file, line);
		std::stringstream ss(line);

		std::vector<double> lineValues;

		std::string delimiter = "\t";
		size_t pos = 0;
		std::string token;

		try
		{
			while ((pos = line.find(delimiter)) != std::string::npos)
			{
				if (line.compare("") == 0)
					break;
				// extract the substr
				token = line.substr(0, pos);
				// push the value to the array
				lineValues.push_back(std::stod(token));
				// erase the data and the delimiter
				line.erase(0, pos + delimiter.length());
			}
			// push the final value into the array
			if (line.compare("") != 0)
				lineValues.push_back(std::stod(line));
		}
		catch (std::invalid_argument e)
		{
			std::cout << "Exception raised at line " << pass << " of the file \"" << filename << "\" => " << e.what() << std::endl;
		}

		if (line.compare("") != 0)
		{
			// read the 4 first entries separated by tabs
			// assign them to the input values
			Sample inputSample;
			for (unsigned int i = 0; i < 4; ++i)
			{
				double value = lineValues[i];
				inputSample.push_back(value);
			}
			m_inputValues.push_back(inputSample);

			// read the 3 last entries separated by tabs
			// assign them to the target values
			Sample targetSample;
			for (unsigned int i = 4; i < lineValues.size(); ++i)
			{
				double value = lineValues[i];
				targetSample.push_back(value);
			}
			m_targetValues.push_back(targetSample);

			++pass;
		}
	}

	file.close();
}

}

//std::string line;
//getline(m_trainingDataFile, line);
//stringstream ss(line);
//
//std::string label;
//ss >> label;
//if (label.compare("in:") == 0)
//{
//	double oneValue;
//	while (ss >> oneValue)
//	{
//		inputVals.push_back(oneValue);
//	}
//}
//
//return inputVals.size();