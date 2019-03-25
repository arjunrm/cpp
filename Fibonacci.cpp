#include <iostream>

int counter = 0;

int calcFibonacci(unsigned int num)
{
	++counter;

	if (num == 1 || num == 0)
	{
		return num;
	}

	return calcFibonacci(num - 2) + calcFibonacci(num - 1);
}

void Fibonacci(unsigned int num)
{
	unsigned int i = 0;
	while (i < num)
	{
		counter = 0;
		std::cout << calcFibonacci(i) << "(";
		std::cout << counter << ") ";
		++i;
	}
}

int main()
{
	Fibonacci(10);

	getchar();
}