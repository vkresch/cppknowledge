// https://www.youtube.com/watch?v=3cm0VckC8q0&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=52
// What is the optimal way of return multiple values?

#include <iostream>
#include <string>
#include <array>
#include <utility>
#include <tuple>

// A way to pass multiple input values and return multiple output values by reference
void FunctionByRefrence(std::string& outVertex, std::string& outFragment){
    outVertex = "outVertex_reference";
    outFragment = "outFragment_reference";
}

// A way to pass multiple input values and return multiple output values by pointer
// This is the more explicit way since you know which variables can be modified
void FunctionByPointer(std::string* outVertex, std::string* outFragment){
    *outVertex = "outVertex_pointer";
    *outFragment = "outFragment_pointer";
}

// Another way can be return an array of strings
std::string* FunctionByNewArray(){
    std::string outVertex = "outVertex_newarray";
    std::string outFragment = "outFragment_newarray";
    return new std::string[2]{outVertex, outFragment};
}

// using the STL array to return
std::array<std::string, 2> FunctionByArray(){
    // vector implementation would be analog whereas it would be a little slower
    // since vector allocates memory on the heap and array allocates on the stack
    std::string outVertex = "outVertex_array";
    std::string outFragment = "outFragment_array";
    std::array<std::string, 2> results;
    results[0] = outVertex;
    results[1] = outFragment;
    return results;
}

// A way to return multiple values even if they are not the same type
// tuple and a pair
std::tuple<std::string, std::string> FunctionByTuple(){
    // vector implementation would be analog whereas it would be a little slower
    // since vector allocates memory on the heap and array allocates on the stack
    std::string outVertex = "outVertex_tuple";
    std::string outFragment = "outFragment_tuple";
    return std::make_pair(outVertex, outFragment);
}

// The best way and intuitive way of return multiple values is to create a struct
struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};
ShaderProgramSource FunctionByStruct(){
    ShaderProgramSource sources;
    sources.VertexSource = "outVertex_struct";
    sources.FragmentSource = "outFragment_struct";    
    return sources;
}

int main(){
    // ==============================================================================
    std::string vs = "";
    std::string fs = "";
    std::cout << vs << ", " << fs << std::endl;

    // ==============================================================================
    FunctionByRefrence(vs, fs);
    std::cout << vs << ", " << fs << std::endl;

    // ==============================================================================
    FunctionByPointer(&vs, &fs);
    std::cout << vs << ", " << fs << std::endl;

    // ==============================================================================
    std::string* shader_ptr = FunctionByNewArray();
    vs = shader_ptr[0];
    fs = shader_ptr[1];
    delete[] shader_ptr; // unfortunatly we use the heap allocation which we need to clear
    std::cout << vs << ", " << fs << std::endl;

    // ==============================================================================
    std::array<std::string, 2> res = FunctionByArray();
    vs = res[0];
    fs = res[1];
    std::cout << vs << ", " << fs << std::endl;

    // ==============================================================================
    // Horrible way of dealing with that because we are not dealing with names 
    // but with numbers which has no meaning for new programmers
    // std::tuple<std::string, std::string> o_tuple = FunctionByTuple();
    auto o_tuple = FunctionByTuple(); // C++11
    vs = std::get<0>(o_tuple);
    fs = std::get<1>(o_tuple);
    std::cout << vs << ", " << fs << std::endl;

    // ==============================================================================
    // Best way to return multiple values even if they are not the same type
    ShaderProgramSource sources = FunctionByStruct();
    vs = sources.VertexSource;
    fs = sources.FragmentSource;
    std::cout << vs << ", " << fs << std::endl;

    return 0;
}