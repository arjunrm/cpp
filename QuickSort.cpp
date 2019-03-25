#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "Timer.h"
#include "Utils.h"

using namespace std;

template <typename T>
vector<T> quickSort(vector<T>& arr)
{
	vector<T> lessList;
	vector<T> moreList;
	vector<T> pivotList;
	vector<T> resultList;

	if (arr.size() <= 1)
		return arr;
	T pivot = arr[0];

	for (size_t i = 0; i < arr.size(); ++i)
	{
		if (arr[i] < pivot)
			lessList.push_back(arr[i]);
		else if (arr[i] > pivot)
			moreList.push_back(arr[i]);
		else
			pivotList.push_back(arr[i]);
	}

	lessList = quickSort(lessList);
	moreList = quickSort(moreList);

	resultList.insert(resultList.end(), lessList.begin(), lessList.end());
	resultList.insert(resultList.end(), pivotList.begin(), pivotList.end());
	resultList.insert(resultList.end(), moreList.begin(), moreList.end());
	return resultList;
}

int main()
{
	vector<int> arr = { 2,8,1,4,14,7,16,10,9,3 };
	printArray<int> pa;

	pa(arr);
	arr = quickSort<int>(arr);
	pa(arr);

	printArray<float> pa2;

	cout << typeid(pa).name() << " " << typeid(pa).before(typeid(pa2)) << " " << typeid(pa2).name() << " " << typeid(pa2).before(typeid(pa));

	cout << endl << endl << sizeof(int) << sizeof(float) << sizeof(long) << sizeof(double) << sizeof(long long);

	unordered_map<string, string> hashMap;
	hashMap.insert(make_pair<string, string>("Arjun", "9886118367"));
	hashMap.emplace("Shravani", "9886232190");
	hashMap.rehash(32);

	cout << endl << endl << "Hashmap:" << endl;
	cout << hashMap.size() << endl;
	cout << hashMap.bucket_count() << endl;
	cout << hashMap.load_factor() << endl;
	for (auto i : hashMap)
	{
		cout << i.first << "," << i.second << "," << hashMap.bucket(i.first) << "," << hashMap.bucket_size(hashMap.bucket(i.first)) << endl;
	}

	vector<string> sampleStr;
	auto itr =  find(sampleStr.begin(), sampleStr.end(), " ");
	itr->erase();

	getchar();
}
