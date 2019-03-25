#include <iostream>
#include <vector>
#include <random>
#include"Timer.h"

int counter = 0;

template <typename T, class Compare_T>
std::vector<T> merge(std::vector<T> left, std::vector<T> right)
{
	Compare_T compare = Compare_T();
	std::vector<T> result;

	// Merge sorted list
	unsigned int left_idx = 0, right_idx = 0;
	while (left_idx < left.size() && right_idx < right.size())
	{
		++counter;
		if (compare(left[left_idx], right[right_idx]))
		{
			result.push_back(left[left_idx]);
			++left_idx;
		}
		else
		{
			result.push_back(right[right_idx]);
			++right_idx;
		}
	}

	if (left_idx < left.size())
		result.insert(result.end(), left.begin() + left_idx, left.end());
	if (right_idx < right.size())
		result.insert(result.end(), right.begin() + right_idx, right.end());

	return result;
}

template <typename T, class Compare_T = std::less<T> >
void mergeSort(std::vector<T>& arr)
{
	counter = 0;

	if (arr.size() <= 1)
		return;

	auto midPoint = arr.size() / 2;
	std::vector<T> left;
	left.insert(left.end(), arr.begin(), arr.begin() + midPoint);
	std::vector<T> right;
	right.insert(right.end(), arr.begin() + midPoint, arr.end());

	mergeSort<T, Compare_T>(left);
	mergeSort<T, Compare_T>(right);
	arr = merge<T, Compare_T>(left, right);
}

int main()
{
	std::vector<int> arr1 = { 43, 56, 12, 1, 99, 2 };
	mergeSort<int>(arr1);

	for (auto i : arr1)
		std::cout << i << " ";
	std::cout << std::endl << "Counter: " << counter;

	std::vector<double> arr2 = { 52.88, 236.13, 9.45, 123.67, 67.12 };
	mergeSort<double, std::greater<double> >(arr2);

	std::cout << std::endl;
	for (auto i : arr2)
		std::cout << i << " ";
	std::cout << std::endl << "Counter: " << counter;

	std::vector<int> arr3;
	for (int i = 0; i < 20000; i++)
	{
		arr3.push_back(rand());
	}

	{
		std::unique_ptr<Timer<> > timer = std::make_unique<Timer<> >();
		mergeSort<int>(arr3);
	}
	std::cout << std::endl << "Counter: " << counter;

	getchar();
}
