#include <iostream>
#include <vector>

int main(){

    std::vector<int> numbers(10);
    for(int i=0;i<numbers.size();i++){
        numbers[i] = i;
    }

    // insert or earase elements in vector
    numbers.erase(numbers.begin() + 3); // Delete element 3 on 4th position
    numbers.insert(numbers.begin(), 123); // Insert 123 at the first position
    
    std::cout << "Capacity: " << numbers.capacity() << std::endl;
    numbers.push_back(10);
    std::cout << "Capacity: " << numbers.capacity() << std::endl; 
    numbers.pop_back();
    std::cout << "Capacity: " << numbers.capacity() << std::endl; 

    // Use it if many deletions has been done and no new addings will be done
    numbers.shrink_to_fit();
    std::cout << "Capacity: " << numbers.capacity() << std::endl; 

    // Change the capacity to 20
    numbers.reserve(20);
    std::cout << "Capacity reserve: " << numbers.capacity() << std::endl; 

    // Resize to 20 elements with default value of 27
    numbers.resize(25, 27);
    std::cout << "Capacity resize: " << numbers.capacity() << std::endl; 

    // Check if numbers are empty
    std::cout << "Is numers empty?: " << numbers.empty() << std::endl;

    // Print the numbers vector
    for(int i=0;i<numbers.size();i++){
        std::cout << numbers[i] << std::endl;
    }

    // Clear the numbers
    numbers.clear();    
    std::cout << "Nothing to print" << std::endl;
    for(int i=0;i<numbers.size();i++){
        std::cout << numbers[i] << std::endl;
    }
    return 0;
}