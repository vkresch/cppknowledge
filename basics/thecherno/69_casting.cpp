// https://www.youtube.com/watch?v=pWZS1MtxI-A&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=69
// Casting
// C++ is a strongly typed language
// There are two types of casts
// C type cast
// C++ type cast
#include <iostream>

class Base {
    public:
        Base(){}
        virtual ~Base(){}
};

class Derived : public Base {
    public:
        Derived(){}
        ~Derived(){}
};

class AnotherClass : public Base {
    public:
        AnotherClass(){}
        ~AnotherClass(){}
};

int main(){
    // Convert an int to a double
    int a = 5;
    // double b = a; // implicit
    double b = (double)a; // C style cast
    std::cout << b << std::endl;

    // Convert a double to an int
    double c = 5.234;
    int d = (int)c; // C style cast
    std::cout << d << std::endl;

    // C++ style cast is a simplified way of casting
    double val = 5.25;
    // A way to be explicit about casting (syntax sugar)
    // A way also to find where you perform casting in your program
    double s = static_cast<int>(val) + 5.3; 
    std::cout << s << std::endl;

    // Class handling
    // This throws a helpful error
    double s = static_cast<AnotherClass*>(val) + 5.3; 

    // Dynamic Cast
    Derived* derived = new Derived();
    Base* base = derived;

    AnotherClass* ac = dynamic_cast<AnotherClass*>(base);
    // reinterpret_cast use the same memory but reinterpret it as another type

    return 0;
}