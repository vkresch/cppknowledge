// https://www.youtube.com/watch?v=4p3grlSpWYA&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=46

#include <iostream>

class Entity {
    public:
        void PrintSomething() const{
            std::cout << "Printing something" << std::endl;            
        }
};

class ScopedPtr {
    private:
        Entity* m_Obj;
    public:
        ScopedPtr(Entity* entity) : m_Obj(entity){}
        ~ScopedPtr(){delete m_Obj;}

        // Overload the arrow operator to ease the calling
        Entity* operator->(){
            return m_Obj;
        }
        const Entity* operator->() const{
            return m_Obj;
        }
};

// Get the offsets of the member variables
struct Vector3 {
    float x, y, z;
};

int main(){
    // Normal way of calling a method from an object
    Entity e;
    e.PrintSomething();

    // Using pointers to call a method
    Entity* eptr = &e;
    (*eptr).PrintSomething();
    eptr->PrintSomething(); // This way of calling is the same way as above but simpler and clearer
    // The -> is an operator which can be overloaded

    {
        ScopedPtr entity = new Entity();
        entity->PrintSomething();
    }

    // Getting the offset
    // BUG (linux): cast from ‘float*’ to ‘int’ loses precision
    // int offset = (int)&((Vector3*)nullptr)->x;
    int offset = (intptr_t)&((Vector3*)nullptr)->z; // FIX: Replace "int" with "intptr_t"
    std::cout << "Offset: " << offset << std::endl; 
    
    return 0;
}