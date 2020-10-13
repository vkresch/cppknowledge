// https://www.youtube.com/watch?v=p4sDgQ-jao4&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=59
// Lambdas is a way to create a function without actually creating a function 
// This is also called an anonymous function
// https://en.cppreference.com/w/cpp/language/lambda

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

void ForEachC(const std::vector<int>& values, void(*func)(int)){
    for(int value: values){
        func(value);
    }
}

void ForEach(const std::vector<int>& values, const std::function<void(int)>& func){
    for(int value: values){
        func(value);
    }
}

int main(){ 
    // Usage example
    std::vector<int> values = { 1, 5, 4, 3, 2};
    auto lambda = [](int value){std::cout << "LambdaValue: " <<value << std::endl;};

    // How to pass a value to a lambda function
    int a = 5;
    auto lambda2 = [&a](int value){std::cout << "LambdaSingleValue: " << a << value << std::endl;};

    ForEachC(values, lambda); // Lambda function
    ForEach(values, lambda2);

    auto it = std::find_if(values.begin(), values.end(), [](int value){return value > 3;});
    std::cout << *it << std::endl;


    return 0;
}