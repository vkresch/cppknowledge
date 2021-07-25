#include <iostream>

struct Point {
    float x;
    float y;
};

struct Person {
    std::string firstName;
    std::string lastName;
    int age;
};

int main(){

    Point p = Point{1.0f, 2.0f};
    std::cout << p.x << std::endl << p.y << std::endl;    

    Person person = Person(); 
    person.age = 27;
    person.firstName = "Max";
    person.lastName = "Mustername";
    std::cout << "First Name: " << person.firstName << std::endl;
    std::cout << "Last Name: " << person.lastName << std::endl;   
    std::cout << "Age: " << person.age << std::endl;

    // Person class can be save into an array
    Person addressBook[10];
    addressBook[0] = person;
    return 0;
}