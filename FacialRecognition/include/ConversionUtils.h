#pragma once

namespace FacialRecognition
{

class ConversionUtils
{
public:
	static auto output_to_class(float* matrix) -> int*
	{
		int test[4] = { 0, 0, 0, 0 };

		int v = 0;

		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				if (matrix[(i * 4) + j] == 1.0f)
					v = j + 1;
			}

			test[i] = v;
			v = 0;
		}

		return test;
	}
};

}