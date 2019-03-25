#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <mutex>
#include <future>
#include <atomic>
#include <condition_variable>
#include "Timer.h"

using namespace std;
mutex mut;

void sharedCout(const char* str)
{
	mutex mut1;
	lock_guard<mutex> guard(mut);
	cout << str << endl;
}

void threadFn(int x, string str)
{
	//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	stringstream ss;
	ss << "ThreadFn Run() " << x << str;
	sharedCout(ss.str().c_str());
}

int recursiveSquare(int x, int count)
{
	int sumOfSquares = 0;

	if (count > 0)
	{
		int temp = x * x;
		sumOfSquares += temp + recursiveSquare(++x, --count);
	}

	return sumOfSquares;
}

void square(int x, unsigned long long count)
{
	unsigned long long sumOfSquares = 0;
	stringstream ss;

	{
		unique_ptr<Timer<>> timer = make_unique<Timer<>>("ms", ss);
		for (int i = 0; i < count; ++i)
		{
			sumOfSquares += (x * x);
			++x;
		}
	}
	ss << "count: " << count << endl << "sumOfSquares: " << sumOfSquares << endl << endl;
	sharedCout(ss.str().c_str());
}

int main()
{
	//thread t1(&threadFn, 99, " Test Thread");
	//sharedCout("Main Thread");

	//t1.join();

	//cout << "Hardware Concurrency: " << t1.hardware_concurrency() << endl;

	//thread t2(&square, 1, 8000000000);
	//thread t3(&square, 1, 7000000000);
	//thread t4(&square, 1, 6000000000);
	//thread t5(&square, 1, 5000000000);

	//auto a = async(&recursiveSquare, 1, 3000);
	//stringstream ss;
	//ss << "Sum of squares a: " << a.get() << endl;
	//sharedCout(ss.str().c_str());

	//thread t6(&square, 1, 4000000000);
	//thread t7(&square, 1, 3000000000);
	//thread t8(&square, 1, 2000000000);
	//thread t9(&square, 1, 1000000000);

	//t2.join();
	//t3.join();
	//t4.join();
	//t5.join();
	//t6.join();
	//t7.join();
	//t8.join();
	//t9.join();

	bool notify = false;
	int value = 100;
	condition_variable cond_var;
	class DerivedConditionVariable : public condition_variable
	{
	public:
		DerivedConditionVariable() : _wakeUpReporter1(false), _wakeUpReporter2(false) {}
		bool _wakeUpReporter1, _wakeUpReporter2;
	}derived_cond_var;
	mutex m;

	thread reporter1([&]() {
		unique_lock<mutex> lock(m);
		while (!derived_cond_var._wakeUpReporter1)
		{
			derived_cond_var.wait(lock);
			cout << endl << endl << "Reporter 1 _wakeUpReporter1,2 : " << derived_cond_var._wakeUpReporter1 << "," << derived_cond_var._wakeUpReporter2;
		}

		cout << endl << endl << "Reporter 1 Value : " << value;
	});

	thread reporter2([&]() {
		unique_lock<mutex> lock(m);
		while (!derived_cond_var._wakeUpReporter2)
		{
			derived_cond_var.wait(lock);
			cout << endl << endl << "Reporter 2 _wakeUpReporter1,2 : " << derived_cond_var._wakeUpReporter1 << "," << derived_cond_var._wakeUpReporter2;
		}

		cout << endl << endl << "Reporterd 2 Value : " << value;
	});

	thread assigner([&]() {
		value = 20;
		derived_cond_var._wakeUpReporter1 = true;
		derived_cond_var.notify_all();
		this_thread::sleep_for(std::chrono::seconds(1));
		derived_cond_var._wakeUpReporter2 = true;
		derived_cond_var.notify_all();

	});

	reporter1.join();
	reporter2.join();
	assigner.join();

	auto labmdaFn = [](int x, int y) { return x + y; }

	getchar();
}
