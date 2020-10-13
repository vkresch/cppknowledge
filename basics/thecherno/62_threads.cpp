// https://www.youtube.com/watch?v=wXBcwHwIt_I&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=62
// g++ -std=c++17 62_threads.cpp -o main -pthread && ./main
// Threads can be executed in parallel

#include <iostream>
#include <thread>

static bool s_Finished = false;

void DoWork(){
    using namespace std::literals::chrono_literals;

    std::cout << "Started thread id= " << std::this_thread::get_id()<<std::endl;

    while(!s_Finished){
        std::cout << "Working ..."<<std::endl;
        std::this_thread::sleep_for(1s);
    }
}

int main(){
    std::cout << "Main thread id= " << std::this_thread::get_id()<<std::endl;
    std::thread worker(DoWork);

    std::cin.get();
    s_Finished = true;

    worker.join();
    std::cout << "Finished\n";
    
}