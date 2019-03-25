#include <iostream>
#include <vector>
#include <random>
#include <memory>
#include "Timer.h"

int static counter = 0;

template <typename T>
void swap(T& x, T& y)
{
	T temp = x;
	x = y;
	y = temp;
}

template <typename T, class Compare_T = std::less<T> >
void bubbleSort(T arr[], int size)
{
	Compare_T compare = Compare_T();

	counter = 0;
	for (int i = 0; i < size; ++i)
	{
		for (int j = size - 1; j > i; j--)
		{
			++counter;
			if (compare(arr[j], arr[j - 1]))
				swap<T>(arr[j], arr[j - 1]);
		}
	}
}

int main()
{
	std::vector<int> arr1 = { 43, 56, 12, 1, 99, 2 };
	bubbleSort<int>(&arr1[0], arr1.size());

	for (auto i : arr1)
		std::cout << i << " ";
	std::cout << std::endl << "Counter: " << counter;

	std::vector<double> arr2 = { 52.88, 236.13, 9.45, 123.67, 67.12 };
	bubbleSort<double, std::greater<double> >(&arr2[0], arr2.size());

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
		bubbleSort<int>(&arr3[0], arr3.size());
	}
	std::cout << std::endl << "Counter: " << counter;

	getchar();
}
