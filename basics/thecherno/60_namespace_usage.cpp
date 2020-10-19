// https://www.youtube.com/watch?v=4NYC-VU-svE&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=60
// Namespace usage
#include <iostream>
#include <algorithm>
#include <string>

/*
Note:
- not using "using namespace std" makes your code explicit
- it shows what belongs to std and what not#
- NEVER YOU using namespace in header files !!!!!!!!!!!!!!!
*/

// using namespace std;

namespace apple {
    void printff(const std::string text){
        std::cout << text << std::endl;
    }
}

namespace orange {
    void printff(const std::string text){
        std::string temp = text;
        std::reverse(temp.begin(), temp.end());
        std::cout << temp << std::endl;
    }
}

using namespace apple;
using namespace orange;

int main(){
    // std::cout << "Print to console" << std::endl;
    printff("Whop");
    return 0;
}