#pragma once

#include <vector>

class OldLayer
{
public:
	OldLayer();
	~OldLayer();

private:
	unsigned int w; // the width of the layer's data (how big the arrays are)
	unsigned int h; // the height of the layer's data (how high the arrays are)
	unsigned int d; // the depth of the layer's data (how many arrays)

	//std::vector<> m_data;
};