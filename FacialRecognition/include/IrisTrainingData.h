#pragma once

#include "TrainingData.h"

namespace FacialRecognition
{

class IrisTrainingData :
	public TrainingData
{
public:
	IrisTrainingData() = delete;
	IrisTrainingData(const std::string& filename);
	~IrisTrainingData() { }
};

}