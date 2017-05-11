// FacialRecognition.cpp : définit le point d'entrée pour l'application console.
//

#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <fstream>

#include "stb_image.h"

#include "NeuralNet.h"
#include "Neuron.h"
#include "ConversionUtils.h"
#include "Utils.h"

#include "IrisTrainingData.h"

#include "MNISTDataReader.h"

using namespace std;
using namespace FacialRecognition;


auto	getImageFile(const std::string& filename, unsigned int& type, std::vector<unsigned int>& red, std::vector<unsigned int>& green, std::vector<unsigned int>& blue) -> void
{
	ifstream file(filename, ios::in | ios::binary);

	for (unsigned int count = 5000; count > 0; --count)
	{
		char typeChar;
		file.read(&typeChar, 1);

		char redBuffer[1024];
		file.read(redBuffer, 1024);

		char greenBuffer[1024];
		file.read(greenBuffer, 1024);

		char blueBuffer[1024];
		file.read(blueBuffer, 1024);

		type = (unsigned char)typeChar;

		for (unsigned int i = 0; i < 1024; ++i)
		{
			red.push_back((unsigned char)redBuffer[i]);
			green.push_back((unsigned char)greenBuffer[i]);
			blue.push_back((unsigned char)blueBuffer[i]);
		}
	}

	file.close();
}


int main()
{
	MNISTDataReader* reader = new MNISTDataReader();

	reader->Read("resources/dataset/train.csv");

	//int x,y,n;
	//unsigned char *data = stbi_load("resources/images/test.png", &x, &y, &n, 0);
	//// ... process data if not NULL ...
	//// ... x = width, y = height, n = # 8-bit components per pixel ...
	//// ... replace '0' with '1'..'4' to force that many components per pixel
	//// ... but 'n' will always be the number that it would have been if you said 0
	//stbi_image_free(data);


	// need an array of pixels
	//unsigned int type;
	//std::vector<unsigned int> redData;
	//std::vector<unsigned int> greenData;
	//std::vector<unsigned int> blueData;

	//getImageFile("resources/images/data_batch_1.bin", type, redData, greenData, blueData);

	//std::vector<unsigned int> imgRed;
	//std::vector<unsigned int> imgGreen;
	//std::vector<unsigned int> imgBlue;

	//// store the first image in the receiving vector
	//for (unsigned int i = 0; i < 1024; ++i)
	//{
	//	imgRed.push_back(redData[i]);
	//	imgGreen.push_back(greenData[i]);
	//	imgBlue.push_back(blueData[i]);
	//}

	

	// prevents console from closing
	getchar();
	return 0;
}







//// Writes XOR training data to a file
//void writeTrainingData(const std::string& fileName, int sampleCount = 2000)
//{
//	ofstream file;
//
//	file.open(fileName);
//
//	file << "topology: 2 4 1" << std::endl;
//	for (int i = sampleCount; i > 0; --i)
//	{
//		int n1 = (int)(2.0 * rand() / double(RAND_MAX));
//		int n2 = (int)(2.0 * rand() / double(RAND_MAX));
//		int t = n1 ^ n2; // should be 0 or 1
//		file << "in: " << n1 << ".0 " << n2 << ".0 " << std::endl;
//		file << "out: " << t << ".0 " << std::endl;
//	}
//
//	file.close();
//}




///////////////////////////
//writeTrainingData("resources/trainingData.txt");
///////////////////////////


///////////////////////////////////////////////////////////////////////////////////

////IrisTrainingData irisTrainingData("resources/iris_training.dat");
////IrisTrainingData irisValidationData("resources/iris_validation.dat");
////IrisTrainingData irisTestData("resources/iris_test.dat");

////// create the neural net based on the topology from the file
////// this could become dynamic once we want to try out more samples in 1 run
////NeuralNet myNet(irisTrainingData.getTopology().data);

////// open a file to write into it
////std::ofstream ostream;
////ostream.open("resources/iris_validation_results.txt");

////double avgError = 1000000;
////int trainingPasses = 0;

////while (trainingPasses < 150)
////{
////	std::cout << "Passes: " << trainingPasses << std::endl;

////	// train the network
////	myNet.train(irisTrainingData, 30);

////	// tmp values
////	std::vector<double> resultVals;
////	int trainingPass = 0;

////	// keep going for as long as there are samples in the array
////	while (trainingPass < irisValidationData.getInputValues().size())
////	{
////		if (trainingPasses == 149) ostream << std::endl << "Pass " << trainingPass;

////		if (trainingPasses == 149)  Utils::printVector(": Inputs:", irisValidationData.getInputValues(trainingPass), ostream);
////		myNet.feedForward(irisValidationData.getInputValues(trainingPass));

////		// collect the neural net's actual results
////		myNet.getResults(resultVals);
////		if (trainingPasses == 149)  Utils::printVector("Outputs:", resultVals, ostream);

////		// Train the neural net on what the output should have been
////		if (trainingPasses == 149)  Utils::printVector("Targets:", irisValidationData.getTargetValues(trainingPass), ostream);
////		myNet.backProp(irisValidationData.getTargetValues(trainingPass));

////		if (trainingPasses == 149)  ostream << "Net recent average error: " << myNet.getRecentAverageError() << std::endl;

////		++trainingPass;
////	}

////	// get the average error
////	avgError = myNet.getRecentAverageError();

////	++trainingPasses;
////}

////if (trainingPasses == 149)  ostream << std::endl << "Done" << std::endl;

////ostream.close();

///////////////////////////////////////////////////////////////////////////////////