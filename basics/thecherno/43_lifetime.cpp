#include <iostream>

class Entity {
    public:
        Entity(){
            std::cout << "Created Entity" << std::endl;
        }

        ~Entity(){
            std::cout << "Destroyed Entity" << std::endl;
        }

        void PrintSomething(Entity* e){
            std::cout << "Printintg something" << std::endl;            
        }
};


int main(){
    Entity* address; 
    {
        Entity* e = new Entity();
        address = e;
    }
    address->PrintSomething(address);
    delete address;
    return 0;
}