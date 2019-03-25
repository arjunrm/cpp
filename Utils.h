#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <iostream>
#include <vector>

template <class T>
struct printArray
{
	void operator()(std::vector<T>& arr)
	{
		std::cout << std::endl;
		for (auto i : arr) { std::cout << i << " "; }
		std::cout << std::endl;
	}
};

#endif // !UTILS_HEADER
