#include <iostream>
#include <vector>
#include "Utils.h"
#include "Timer.h"

int counter = 0;

template <typename T, class Compare_T = std::less<T> >
void insertionSort(std::vector<T>& arr)
{
	Compare_T compare = Compare_T();
	printArray<T> printArr;

	for (auto i = 1; i < arr.size(); ++i)
	{
		auto temp = arr[i];
		auto j = i - 1;
		while (j >= 0 && (compare(temp, arr[j])))
		{
			++counter;
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j + 1] = temp;

		if (arr.size() < 20)
			printArr(arr);
	}
}

int main()
{
	printArray<int> paInt;
	printArray<double> paDouble;

	std::vector<int> arr1 = { 43, 56, 12, 1, 99, 2 };
	paInt(arr1);
	insertionSort<int>(arr1);

	for (auto i : arr1)
		std::cout << i << " ";
	std::cout << std::endl << "Counter: " << counter;

	std::vector<double> arr2 = { 52.88, 236.13, 9.45, 123.67, 67.12 };
	paDouble(arr2);
	insertionSort<double, std::greater<double> >(arr2);

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
		insertionSort<int>(arr3);
	}
	std::cout << std::endl << "Counter: " << counter;

	getchar();
}
