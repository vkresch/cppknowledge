// https://www.youtube.com/watch?v=oEx5vGNFrLk&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=63
// http://en.cppreference.com/w/cpp/chrono
#include <iostream>
#include <thread>
#include <chrono>

// Setup a class timer
// The idea is to use the life time object cycle to time functions
struct Timer {
    std::chrono::_V2::system_clock::time_point start, end;
    std::chrono::duration<float> duration;

    Timer(){
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer(){
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;

        float ms = duration.count() * 1000.0f;
        std::cout << "Timer took " << ms << " ms" << std::endl;
    }
};

void Function(){
    Timer timer;
    using namespace std::literals::chrono_literals;
    std::this_thread::sleep_for(1s);
    for(int i= 0; i<100; i++)
        std::cout << "Hello" << std::endl;
}

int main(){
    // Naive way of timing a function
    using namespace std::literals::chrono_literals; // Enable to use in 1s

    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(1s);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> duration = end - start;
    std::cout << duration.count() << " s" << std::endl;

    // Simple call to function
    Function();

    return 0;
}