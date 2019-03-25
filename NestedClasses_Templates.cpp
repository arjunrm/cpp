// Example program
#include <iostream>
#include <string>

class A
{
    public:
    int x;

    A() : x(50) {}
    
    class B
    {
        public:
        int y;
        
        B() : y(20) {}
        
        void show(A& a)
        {
            std::cout << "x = " << a.x << std::endl;
        }
    };
    
    void show(B& b)
    {
        std::cout << "y = " << b.y << std::endl;
    }
    
};

template <typename T>
void run(T a)
{
    std::cout << "Run : " << a << std::endl;
}

template <>
void run(float a)
{
    std::cout << "Float Run : " << a << std::endl;
}

template <class T, int x>
class TemplateSpecialization
{
    public:
    void traverse(T a)
    {
        std::cout << "Traverse(" << a << "," << x << ")" << std::endl;
    }
};

template <>
class TemplateSpecialization <char, 1000>
{
    public:
    void traverse(char a)
    {
        std::cout << "TraverseChar(" << a << "," << 1000 << ")" << std::endl;
    }
};

template <int n>
struct MetaProgrammingTemplate
{
    enum { val = 2*MetaProgrammingTemplate<n-1>::val };
};

template <>
struct MetaProgrammingTemplate <0>
{
    enum { val = 1 };
};

int main()
{
    A a;
    A::B b;
    a.show(b);
    b.show(a);
    
    run<int>(10);
    run<float>(5.0);
    run<char>('a');
    
    TemplateSpecialization<int, 500> t1;
    TemplateSpecialization<float, 30> t2;
    TemplateSpecialization<char, 1000> t3;
    
    t1.traverse(10);
    t2.traverse(50.0f);
    t3.traverse('z');
    
    std::cout << "MetaProgrammingTemplate(" << MetaProgrammingTemplate<4>::val << ")" << std::endl;
}
