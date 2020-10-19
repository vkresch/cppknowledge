// https://www.youtube.com/watch?v=ts1Eek5w7ZA&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=61
// Namespace usage
#include <iostream>
#include <algorithm>
#include <string>

namespace apple {
    namespace nested {
        void printff(const std::string text){
            std::cout << text << std::endl;
        }
    }
}

namespace orange {
    void printff(const std::string text){
        std::string temp = text;
        std::reverse(temp.begin(), temp.end());
        std::cout << temp << std::endl;
    }
}

int main(){
    // When defining namespaces inside functions
    // They are only accesible in the function scope
    // here only in main
    using namespace apple;
    using namespace orange;

    // std::cout << "Print to console" << std::endl;
    apple::nested::printff("Whop");

    // Implicit function usage
    printff("Whop");

    // Partial namespace
    nested::printff("Another");

    // Define an alias for a long namespace
    namespace an = apple::nested;
    an::printff("huuuuuuuuuuu");
    return 0;
}