// https://www.youtube.com/watch?v=wJ1L2nSIV1s&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=54
// Stack and Heap are stored in memory (RAM)
// Both allocate memory in a different way
#include <iostream>
#include <string>

struct Vector3 {
    float x, y, z;
    Vector3(float x, float y, float z): x(x), y(y), z(z){}
};

std::ostream& operator<<(std::ostream& stream, Vector3& vec){
    stream << vec.x << ", " << vec.y << ", " <<  vec.z;
    return stream;
}

int main(){
    // ==============================================================
    // Stack allocation
    // Memory allocation is in order like a stack of memory :)
    // Extremly fast
    int value = 5; 
    std::cout << value << std::endl;

    int array[5] = {1, 2, 3, 4, 5}; // array stack allocation

    Vector3 vector(1,2,3);
    std::cout << vector << std::endl;

    // ==============================================================
    // Heap allocation
    // The new keyword is just a call to malloc
    // Then it will go through a freelist to get free memory
    // and return a pointer to that and then it will log small things 
    // (a lot of book keeping so overhead)
    // when asking for more memory it is even than more expensive 
    // in terms of performance
    int* value_ptr = new int(5);
    std::cout << *value_ptr << std::endl;
    delete value_ptr;

    int* array_ptr = new int[5]; // array heap allocation
    delete[] array_ptr;

    Vector3* vector_ptr = new Vector3(1, 2, 3);
    delete vector_ptr;

    return 0;
}