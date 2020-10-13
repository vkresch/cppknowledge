// https://www.youtube.com/watch?v=p4sDgQ-jao4&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=58
// Raw function pointers come from C

#include <iostream>
#include <vector>

void HelloWorld(){
    std::cout << "Hello World!" << std::endl;
}

void HelloWorldValue(int a){
    std::cout << "Hello World! Value: " << a << std::endl;
}

void PrintValue(int value){
    std::cout << "Value: " <<value << std::endl;
}

void ForEach(const std::vector<int>& values, void(*func)(int)){
    for(int value: values){
        func(value);
    }
}

int main(){ 
    
    // Confusing way of assigning a function to a variable
    void(*anotherfunc)() = HelloWorld;
    anotherfunc();
    std::cout << "--------" << std::endl;

    // The & is explicit
    // Another way of assigning which is simpler
    auto function = &HelloWorld;
    function();
    std::cout << "--------" << std::endl;

    // Another way can be with typedef
    typedef void(*functype)();
    functype function_simple = HelloWorld;
    function_simple();
    std::cout << "--------" << std::endl;

    // Assign the typedef with an argument
    typedef void(*functypearg)(int);
    functypearg function_arg = HelloWorldValue;
    function_arg(123);
    std::cout << "--------" << std::endl;

    // Using the auto assignment with an argument
    auto function_autoarg = &HelloWorldValue;
    function_autoarg(321);
    std::cout << "--------" << std::endl;

    // Usage example
    std::vector<int> values = { 1, 5, 4, 3, 2};
    ForEach(values, PrintValue);
    ForEach(values, HelloWorldValue);
    ForEach(values, [](int value){std::cout << "LambdaValue: " <<value << std::endl;}); // Lambda function
    return 0;
}