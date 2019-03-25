#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

auto make_function(int& x, int y)
{
	return [&x, y]() { cout << " X: " << x << " Y:" << y << endl; };
}

class MoveCtr
{
public:
	MoveCtr() : _x(10), _y(20) {}
	MoveCtr(int x, int y) { _x = x; _y = y; }

	MoveCtr(MoveCtr& obj)
	{
		cout << "copy ctr" << endl;
		_x = obj._x;
		_y = obj._y;
	}

	void operator=(const MoveCtr& obj)
	{
		cout << "operator=" << endl;
		_x = obj._x;
		_y = obj._y;
	}

	// prefix operator
	void operator++()
	{
		cout << "operator++" << endl;
		_x += 2;
		_y += 4;
	}

	void operator++(int)
	{
		cout << "operator++(int)" << endl;
		_x += 3;
		_y += 5;
	}

	MoveCtr(MoveCtr&& obj)
	{
		cout << "move copy ctr" << endl;
		_x = obj._x;
		_y = obj._y;
	}

	void operator=(const MoveCtr&& obj)
	{
		cout << "move operator=" << endl;
		_x = obj._x;
		_y = obj._y;
	}

	MoveCtr moveFunc(MoveCtr obj)
	{
		cout << "moveFunc" << endl;
		return obj;
	}

	int _x, _y;
};

int main()
{
	int i = 10;
	int j = 30;
	auto f = make_function(i, j);
	f();

	i = 20;
	j = 40;
	f();

	int a = 1, b = 1, c = 1;

	auto m1 = [a, &b, &c]() mutable {
		auto m2 = [a, b, &c]() mutable {
			cout << "a,b,c: " << a << b << c << endl;
			a = 4; b = 4; c = 4;
		};
		a = 3; b = 3; c = 3;
		m2();
	};

	a = 2; b = 2; c = 2;
	m1();

	cout << "a,b,c: " << a << b << c << endl;

	size_t size = 0;
	auto printFn = [&size](auto x) { --size;  cout << x << " "; if (size == 0) cout << endl << endl; };

	vector<int> v1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	size = v1.size();
	for_each(v1.begin(), v1.end(), printFn);

	int x = 5;
	auto itr = v1.erase(remove_if(v1.begin(), v1.end(), [x](int i) { return i < x; }), v1.end());
	size = v1.size();
	for_each(v1.begin(), v1.end(), printFn);

	for_each(v1.begin(), v1.end(), [](int &x) { x *= 2; });
	size = v1.size();
	for_each(v1.begin(), v1.end(), printFn);

	MoveCtr obj1 = {10, 20};
	MoveCtr obj2 = obj1; // copy ctr
	MoveCtr obj3;
	obj3 = obj1; // operator=
	MoveCtr obj4(obj3); // copy ctr
	++obj1;
	obj2++;

	obj4 = obj1.moveFunc(MoveCtr());
	cout << "break" << endl;
	obj2 = move(obj3);

	getchar();

	return 0;
}
