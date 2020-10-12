// https://www.youtube.com/watch?v=BvR1Pgzzr38&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=45

#include <iostream>
#include <string.h> // C function

// Custom 2d Vector
struct Vector2{
    float x, y;
};

// Custom string function
class String{
    private:
        char* m_Buffer;
        unsigned int m_Size;
    public:
        String(const char* cstring){
            m_Size = strlen(cstring);
            m_Buffer = new char[m_Size + 1];
            memcpy(m_Buffer, cstring, m_Size);
            m_Buffer[m_Size] = 0; // Adding the null terminator manually
        }

        // This code performs a deep copy
        String(const String& other) : m_Size(other.m_Size){
            std::cout << "Copying ..." << std::endl;
            m_Buffer = new char[m_Size + 1];
            memcpy(m_Buffer, other.m_Buffer, sizeof(m_Size + 1));
        }

        // Copy constructor gets called when you make a copy
        // String(const String& other) : m_Buffer(other.m_Buffer), m_Size(other.m_Size){
        // }

        // Similar way of copying with memcpy
        // String(const String& other){
        //     memcpy(this, &other, sizeof(String));
        // }

        // Delete the copy constructor so that we do not allow copy
        // String(const String& other) = delete;

        ~String(){
            delete[] m_Buffer;
        }

        // Overload the index operator
        char& operator[](unsigned int index){
            return m_Buffer[index];
        }

        // Friend defines function which are allowed to access private variables
        friend std::ostream& operator<<(std::ostream& stream, const String& string);
};

// Overloading << operator so that we can print to the console
std::ostream& operator<<(std::ostream& stream, const String& string){
    stream << string.m_Buffer;
    return stream;
};

// This function can be optimized by "const String& s" pass by reference
// Always try to pass by const reference
void PrintSomething(String s){
    std::cout << s << std::endl;
}

int main(){
    // this example is analog to classes
    int a = 2;
    int b = a; // this is a copy of a
    b = 3; // a will remain 2

    // this copies the address not the values
    Vector2* c = new Vector2();
    Vector2* d = c;
    d->x = 2; // this will affect both because they both point to the same address

    String string = "Viktor";
    String second = string; // This is a shallow copy with the default copy constructor
    second[2] = 'a';

    std::cout << string << std::endl;
    std::cout << second << std::endl; // BUG: The word is not displayed till the end.

    PrintSomething(string); // We make unneccecery copying
    PrintSomething(second); // We make unneccecery copying

    return 0;
}