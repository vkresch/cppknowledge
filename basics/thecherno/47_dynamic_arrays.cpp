// https://www.youtube.com/watch?v=PocJ5jXv8No&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=47
// Now we need to get accostumed to the STL (Standard Template Library)
// STL is not that fast
// EA has  developed their own STL library: https://github.com/electronicarts/EASTL

#include <iostream>
#include <string>
#include <vector>

struct Vertex {
    float x, y, z;
};

std::ostream& operator<<(std::ostream& stream, const Vertex& vertex){
    stream << vertex.x << ", " << vertex.y << ", " << vertex.z;
    return stream;
}

// Passing vectors around should always be done by const reference
// by doing that you ensure that you are not copying that entire vector array
void Function(const std::vector<Vertex>& vertex_vector){
    for(const Vertex& v: vertex_vector){
        std::cout << v << std::endl;
    }
}

int main(){
    Vertex vertices[5]; // Generate array on stack
    Vertex* vertices_ptr = new Vertex[5]; // Generate array on the heap

    // If you want to use a dynamic size use vector
    std::vector<Vertex> vertices_vec;
    vertices_vec.push_back({1, 2, 3});
    vertices_vec.push_back({5, 3, 3});

    // Pass by reference vector IMPORTANT!
    Function(vertices_vec);

    // Normal way to iterate over a vector
    for(int i = 0; i < vertices_vec.size(); i++){
        std::cout << vertices_vec[i] << std::endl;
    }

    // Range based for loop with copying
    for(Vertex v: vertices_vec){
        std::cout << v << std::endl;
    }

    // Range based for loop without copying (optimal way)
    for(const Vertex& v: vertices_vec){
        std::cout << v << std::endl;
    }

    // Remove all vertices
    // vertices_vec.clear();

    // Or erase one element of the vertex vector
    vertices_vec.erase(vertices_vec.begin() + 1);

    for(const Vertex& v: vertices_vec){
        std::cout << v << std::endl;
    }

    return 0;
}