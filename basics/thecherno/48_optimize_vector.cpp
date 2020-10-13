// https://www.youtube.com/watch?v=HcESuwmlHEY&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=48
// How to use the std::vector class in an optimal way
// C++ is a language which plays nicely with optimization
// Rule number 1 of optimization is knowing your environment
// Optimization strategy for the vector class is to make sure to avoid copying (see for more on copy 45_copying.cpp)

#include <iostream>
#include <string>
#include <vector>

struct Vertex {
    float x, y, z;
    Vertex(float x, float y, float z) : x(x), y(y), z(z){}

    // Add a copy constructor to check when it is called
    Vertex(const Vertex& v) : x(v.x), y(v.y), z(v.z){
        std::cout << "Copied!" << std::endl;
    }
};

std::ostream& operator<<(std::ostream& stream, const Vertex& vertex){
    stream << vertex.x << ", " << vertex.y << ", " << vertex.z;
    return stream;
}

int main(){

    // If you want to use a dynamic size use vector
    // C++ copies the vertex 6 times
    std::vector<Vertex> vertices;
    vertices.push_back(Vertex(1, 2, 3)); // First copy from main into the vector can be avoided
    vertices.push_back(Vertex(5, 3, 3)); // Copies the second on to memory with capacity of two and then appends to this memory 2 copies
    vertices.push_back(Vertex(1, 1, 1)); // Tell the vector from the start how many vertices we gonna push

    std::cout << "------" << std::endl;

    // Optimization reserve capacity for vector
    // Reduces from 6 copies -> 3 copies
    std::vector<Vertex> vertices_opt1;
    vertices_opt1.reserve(3); // Reserve makes sure that we have enough memory
    vertices_opt1.push_back(Vertex(1, 2, 3));
    vertices_opt1.push_back(Vertex(5, 3, 3));
    vertices_opt1.push_back(Vertex(1, 1, 1));

    std::cout << "------" << std::endl;

    // Optimization reserve capacity for vector
    // Reduces from 3 copies -> 0 copies
    std::vector<Vertex> vertices_opt2;
    vertices_opt2.reserve(3); // Reserve makes sure that we have enough memory
    vertices_opt2.emplace_back(1, 2, 3);
    vertices_opt2.emplace_back(5, 3, 3);
    vertices_opt2.emplace_back(1, 1, 1);

    // Check the content of the vector
    for(const Vertex& v: vertices_opt2){
        std::cout << v << std::endl;
    }

    return 0;
}