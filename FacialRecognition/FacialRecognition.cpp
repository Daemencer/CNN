// FacialRecognition.cpp : définit le point d'entrée pour l'application console.
//

#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <fstream>

#include "NeuralNet.h"
#include "Neuron.h"
#include "ConversionUtils.h"
#include "Utils.h"

#include "IrisTrainingData.h"

using namespace std;
using namespace FacialRecognition;


// Writes XOR training data to a file
void writeTrainingData(const std::string& fileName, int sampleCount = 2000)
{
	ofstream file;

	file.open(fileName);

	file << "topology: 2 4 1" << std::endl;
	for (int i = sampleCount; i > 0; --i)
	{
		int n1 = (int)(2.0 * rand() / double(RAND_MAX));
		int n2 = (int)(2.0 * rand() / double(RAND_MAX));
		int t = n1 ^ n2; // should be 0 or 1
		file << "in: " << n1 << ".0 " << n2 << ".0 " << std::endl;
		file << "out: " << t << ".0 " << std::endl;
	}

	file.close();
}


int main()
{
	/////////////////////////
	writeTrainingData("resources/trainingData.txt");
	/////////////////////////


	/////////////////////////////////////////////////////////////////////////////////

	IrisTrainingData irisTrainingData("resources/iris_training.dat");
	IrisTrainingData irisValidationData("resources/iris_validation.dat");
	IrisTrainingData irisTestData("resources/iris_test.dat");

	// create the neural net based on the topology from the file
	// this could become dynamic once we want to try out more samples in 1 run
	NeuralNet myNet(irisTrainingData.getTopology().data);

	// open a file to write into it
	std::ofstream ostream;
	ostream.open("resources/iris_validation_results.txt");

	double avgError = 1000000;
	int trainingPasses = 0;

	while (trainingPasses < 150)
	{
		std::cout << "Passes: " << trainingPasses << std::endl;

		// train the network
		myNet.train(irisTrainingData, 30);

		// tmp values
		std::vector<double> resultVals;
		int trainingPass = 0;

		// keep going for as long as there are samples in the array
		while (trainingPass < irisValidationData.getInputValues().size())
		{
			if (trainingPasses == 149) ostream << std::endl << "Pass " << trainingPass;

			if (trainingPasses == 149)  Utils::printVector(": Inputs:", irisValidationData.getInputValues(trainingPass), ostream);
			myNet.feedForward(irisValidationData.getInputValues(trainingPass));

			// collect the neural net's actual results
			myNet.getResults(resultVals);
			if (trainingPasses == 149)  Utils::printVector("Outputs:", resultVals, ostream);

			// Train the neural net on what the output should have been
			if (trainingPasses == 149)  Utils::printVector("Targets:", irisValidationData.getTargetValues(trainingPass), ostream);
			myNet.backProp(irisValidationData.getTargetValues(trainingPass));

			if (trainingPasses == 149)  ostream << "Net recent average error: " << myNet.getRecentAverageError() << std::endl;

			++trainingPass;
		}

		// get the average error
		avgError = myNet.getRecentAverageError();

		++trainingPasses;
	}

	if (trainingPasses == 149)  ostream << std::endl << "Done" << std::endl;

	ostream.close();

	/////////////////////////////////////////////////////////////////////////////////


	// prevents console from closing
	getchar();
	return 0;
}