#include <iostream>
#include <string>
#include <memory>

class SharedClass
{
public:
	int x = 100;
	std::string _str = "Default";
	explicit SharedClass(std::string str) : _str(str) { std::cout << std::endl << "SharedClass():" << _str.c_str(); }
	SharedClass() { std::cout << std::endl << "SharedClass()"; }
	~SharedClass() { std::cout << std::endl << "~SharedClass():" << _str.c_str(); }
};

int main()
{
	{
		//std::shared_ptr<SharedClass> shPtr1(new SharedClass);

		// This approach is faster and safer
		// faster - as this avoid creating SharedClass obj and then shared_ptr obj
		// safer - if SharedClass obj has been created successfully but if shared_ptr fails then we have mem leak
		std::shared_ptr<SharedClass> shPtr1 = std::make_shared<SharedClass>("shPtr1");
		std::cout << std::endl << shPtr1.use_count() << " x:" << shPtr1->x;

		{
			std::shared_ptr<SharedClass> shPtr2 = shPtr1;
			shPtr2->x = 20;
			std::cout << std::endl << shPtr2.use_count() << " x:" << shPtr2->x;
		}

		// If we need to use custom deleter then we need to use std::shared_ptr() directly instead of std::make_shared<>()
		std::shared_ptr<SharedClass> shPtr3(new SharedClass("shPtr3"), [](SharedClass* p) { std::cout << std::endl << "Custom delete"; delete p; });

		// If we use new[] then there will be mem leak as std::make_shared used delete NOT delete[]
		// so we need to use custom deleter
		std::shared_ptr<SharedClass> shPtr4(new SharedClass[3], [](SharedClass* p) { std::cout << std::endl << "Custom delete[]"; delete[] p; });

		std::unique_ptr<SharedClass> unPtr1 = std::make_unique<SharedClass>("unPtr1");
		std::unique_ptr<SharedClass> unPtr2;
		unPtr2.swap(unPtr1);

		std::cout << std::endl << shPtr1.use_count();

		std::cout << std::endl << "shPtr4 x: " << shPtr4->x;
		std::weak_ptr<SharedClass> wkPtr1 = shPtr4;
		wkPtr1.lock()->x = 300;
		std::cout << std::endl << "wkPtr1(shPtr4) x: " << wkPtr1.lock()->x;
	}

	getchar();
}
