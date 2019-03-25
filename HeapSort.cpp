#include <iostream>
#include <vector>
#include "Utils.h"
#include "Timer.h"

using namespace std;

template <typename T>
void swapElem(T& x, T& y)
{
	T temp = x;
	x = y;
	y = temp;
}

template <typename T>
void maxHeapify(std::vector<T>& arr, size_t heapSize, unsigned int index)
{
	auto left = index * 2 + 1;
	auto right = index * 2 + 2;
	auto parent = index;

	if (left < heapSize && arr[left] > arr[parent])
		parent = left;
	if (right < heapSize && arr[right] > arr[parent])
		parent = right;
	if (parent != index)
	{
		swapElem<T>(arr[parent], arr[index]);
		maxHeapify<T>(arr, heapSize, parent);
	}
}

template <typename T>
void buildHeap(std::vector<T>& arr)
{
	printArray<T> pa;

	cout << "Before buildHeap:";
	pa(arr);

	for (int i = arr.size() / 2; i >= 0; --i)
	{
		maxHeapify<T>(arr, arr.size() - 1, i);
	}

	cout << "After buildHeap:";
	pa(arr);
}

template <typename T>
void heapSort(vector<T>& arr)
{
	size_t heapSize = arr.size();
	buildHeap<T>(arr);

	for (int i = heapSize - 1; i >= 0; --i)
	{
		swapElem<T>(arr[i], arr[0]);
		maxHeapify<T>(arr, i, 0);
	}
}

int main()
{
	vector<int> arr = { 2,8,1,4,14,7,16,10,9,3 };

	heapSort<int>(arr);

	cout << "Result:";
	printArray<int> pa;
	pa(arr);

	getchar();

	return 0;
}

