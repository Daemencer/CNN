#pragma once

#include <iostream>
#include <string>

class Utils
{
public:
	template <typename T>
	static auto printVector(const std::string& label, const std::vector<T>& v, std::ostream& s) -> void
	{
		s << label.c_str() << " [ ";
		for (unsigned int i = 0; i < v.size(); ++i)
		{
			if (i != v.size() - 1)
				s << v[i] << ", ";
			else
				s << v[i] << " ";
		}
		s << "]" << std::endl;
	}
};