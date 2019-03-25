#include <stdio.h>
#include <iostream>
#include <vector>
#include <initializer_list>

class myVector
{
public:
	std::vector<int> _vec;
	myVector(const std::initializer_list<int>& v)
	{
		for (std::initializer_list<int>::iterator itr = v.begin();
			itr != v.end(); ++itr)
			_vec.push_back(*itr);
	}
};

class UniformInitializer
{
public:
	UniformInitializer(int age, std::string name) 
	{
		std::cout << age << " " << name.c_str() << std::endl;
	}
};

// enum class
enum class apple { green, red };
enum class orange { big, small };

bool operator==(apple& a, orange& b)
{
	return (int)a == (int)b;
}

// Deligating Constructor
class DeligatingConstructor
{
public:
	int x, y = 5, z = 20;
	DeligatingConstructor() { x = 10;  }
	DeligatingConstructor(int a)
		: DeligatingConstructor()
	{
		y = a;
	}

	DeligatingConstructor(int a, int b)
		: DeligatingConstructor(a)
	{
		z = b;
	}
};

// constexpr
constexpr int cubed(int x) { return x * x * x; }

// templated constexpr
template <class T>
constexpr T squared(T x) { return x * x; }

// lambda function
template <class T_func>
void multiply(T_func f, std::vector<int>& v)
{
	std::cout << std::endl;
	for (auto& i : v)
	{
		f(i);
		std::cout << i << " ";
	}
}

int main()
{
	// cancels rounding off of float
	std::cout << std::fixed;

	// Initializer List
	std::vector<int> v = { 1, 2, 3, 4 };
	std::cout << v[0] << std::endl;

	myVector myV = { 5, 4, 3, 2, 1 };
	std::cout << myV._vec[0] << std::endl;

	// Uniform Initialization Search Order
	// 1. initializer_list
	// 2. Regular contructor
	// 3. Aggregate initializer
	UniformInitializer aggInit = { 34, "Arjun" };

	// auto type
	std::cout << "Auto Type : ";
	for (auto itr = v.begin(); itr != v.end(); ++itr)
	{
		(*itr) *= 2;
		std::cout << *itr << " ";
	}

	std::cout << std::endl;

	// foreach
	std::cout << "Foreach : ";
	for (auto& i : v)
	{
		i *= 2;
		std::cout << i << " ";
	}

	// enum class
	apple a = apple::green;
	apple b = apple::red;
	orange o = orange::small;

	std::cout << std::endl << ((a == o) ? "True" : "False");

	// Deligating Constructor
	DeligatingConstructor dc1;
	DeligatingConstructor dc2(30);
	DeligatingConstructor dc3(40, 50);

	std::cout << std::endl << dc1.x << " " << dc1.y << " " << dc1.z;
	std::cout << std::endl << dc2.x << " " << dc2.y << " " << dc2.z;
	std::cout << std::endl << dc3.x << " " << dc3.y << " " << dc3.z;

	// constexpr
	const int cubeOf3 = cubed(3);
	const int cubeOf12 = cubed(12);

	std::cout << std::endl << cubeOf3;
	std::cout << std::endl << cubeOf12;

	const float squaredOf4 = squared<float>(4.0);
	const short squaredOf11 = squared<short>(11);

	std::cout << std::endl << squaredOf4;
	std::cout << std::endl << squaredOf11;

	// lambda function
	auto lamdaAdd = [](int x, int y) { return x + y; };
	std::cout << std::endl << lamdaAdd(3, 4);

	auto lamdaMultiply = [](auto& x) { x *= 10; };
	std::vector<int> lambdaVec = { 5, 6, 7, 8 };

	multiply(lamdaMultiply, lambdaVec);

	getchar();
}
