#include <iostream>
#include <functional>

class SampleFunctor
{
public:
	SampleFunctor() : _counter(0) {}
	int operator()(int x) { return _counter += x; }
	int count(int x) { return _counter += x; }
	void display() { std::cout << std::endl << _counter; }
private:
	int _counter;
};

int main()
{
	SampleFunctor s1, s2;
	s1(10); s1.display();
	s1(20); s1.display();
	s1(30); s1.display();

	s2.count(10); s2.display();
	s2.count(20); s2.display();
	s2.count(30); s2.display();

	std::function< int(int, int) > fn[] = { std::plus<int>(), std::minus<int>(), std::multiplies<int>(), std::divides<int>() };

	for (auto& f : fn)
	{
		std::cout << std::endl << f(15, 10);
	}

	getchar();
}
