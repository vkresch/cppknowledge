// https://www.youtube.com/watch?v=8egZ_5GA9Bc&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=66
// Type punning
// Getting around with the C++ type system
#include <iostream>

struct Entity {
    int x, y;
};

int main(){
    int a = 50;

    // Implicit conversion
    double d_value = a; 

    // Explicit conversion
    double d_value2 = (double)a; 

    // This is called type punning an integer to a double
    // We stored 4 bytes of int memory into 8 bytes of double memory
    double value_new = *(double*)&a; // Convert an int pointer to a double pointer
    std::cout << value_new << std::endl;

    // The object is just made up of those two integers
    // There is not much more memory than that allocated
    Entity e = {5, 8}; 

    // We can access the attributes of the struct like an array
    int* position = (int*)&e;
    std::cout << position[0] << ", " << position[1] << std::endl;

    int y = e.y; // Normal way to acces e.y
    // The raw method below should not be used in real life applications
    int y2 = *(int*)((char*)&e + 4); // raw memory access method to access y
    std::cout << y << ", " << y2 << std::endl;
    return 0;
}