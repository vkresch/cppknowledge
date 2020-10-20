// https://www.youtube.com/watch?v=x0uUKWJzSO4&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=65
// Sorting
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

// Override the << operator to print a vector of ints like in python
std::ostream& operator<<(std::ostream& stream, const std::vector<int>& vecs){
    stream << "[";
    for(int vec: vecs){
        stream << vec << ", ";
    }
    stream << "]";
    return stream;
}

int main(){
    std::vector<int> values = {1, 3, 0, 7, 6};
    std::cout << values << std::endl;

    // Do a default sort
    std::sort(values.begin(), values.end());
    std::cout << values << std::endl;

    // Pass a builtin function into sort
    std::sort(values.begin(), values.end(), std::greater<int>());
    std::cout << values << std::endl;

    // Pass a lambda function to sort
    std::sort(values.begin(), values.end(), [](int a, int b){return a < b;});
    std::cout << values << std::endl;
    std::sort(values.begin(), values.end(), [](int a, int b){return a > b;});
    std::cout << values << std::endl;
    return 0;
}