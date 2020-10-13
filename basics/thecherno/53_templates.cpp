// https://www.youtube.com/watch?v=I-hZkUa9mIs&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=53
// Templates are like powerful macros
// Templates allow you to define a template that will be compiled by your usage
// The compiler writes code for you based on a set of rules
#include <iostream>
#include <string>

// ==============================================================
// If we want to have the same function to take in two different types
// we normally would define two functions
// void Print(const int& value){
//     std::cout << value << std::endl;
// }

// void Print(const std::string& value){
//     std::cout << value << std::endl;
// }

// ==============================================================
// A template is not real code or even a function
// It does not exist until we call it!!
// This only gets created when we actually call it
// typename == class
template<typename T>
void Print(const T& value){
    std::cout << value << std::endl;
}

// ==============================================================
// Use template for a class instead of a function
template<typename T, int N>
class Array {
    private:
        T m_Array[N];
    public:
        int GetSize() const {
            return N;
        }
};

int main(){
    // ==============================================================
    // One can call the function implicit or explicit like below
    Print<int>(1); // Print an int
    Print<std::string>("Hello"); // Print an string
    Print("Another String");
    Print<float>(5.5f);

    // ==============================================================
    // This is called meta programming 
    // We are programming on compiletime not runtime
    Array<std::string, 50> array;
    std::cout << array.GetSize() << std::endl;

    return 0;
}