#include <iostream>

enum Example : unsigned int {
    A, B, C
};

int main(){
    Example value = C;
    std::cout << value << std::endl;
    return 0;
}