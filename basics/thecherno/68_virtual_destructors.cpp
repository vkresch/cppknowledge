// https://www.youtube.com/watch?v=jELbKhGkEi0&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=68
// Virtual Destructors
// Virtual Destructors are important when you are dealing with polymorphism
#include <iostream>

class Base {
    public:
        Base(){ std::cout << "Base Constructed" << std::endl;}
        virtual ~Base(){ std::cout << "Base Destructed" << std::endl;}
};

class Derived : public Base {
    public:
        Derived(){ std::cout << "Derived Constructed" << std::endl;}
        ~Derived(){ std::cout << "Derived Destructed" << std::endl;}
};

int main(){
    Base* base = new Base();
    delete base;

    std::cout << "---------------" << std::endl;

    Derived* derived = new Derived();
    delete derived;

    std::cout << "---------------" << std::endl;
    // Poly type
    // Derived destructor is not called if base is not virtual
    // This can cause a memory leak
    Base* poly = new Derived();
    delete poly;
    /*
    Note:
    - when you create a class that will be subclassed you need to make a virtual destructor
    
    */

    return 0;
}