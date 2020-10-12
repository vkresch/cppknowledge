#include <iostream>
#include <string>
#include <memory>

class Entity {
    public:
        Entity(){
            std::cout << "Created Entity" << std::endl;
        }

        ~Entity(){
            std::cout << "Destroyed Entity" << std::endl;
        }

        void PrintSomething(){
            std::cout << "Something" << std::endl;
        }
};


int main(){
    {
        // std::unique_ptr<Entity> entity(new Entity());
        std::unique_ptr<Entity> entity = std::make_unique<Entity>(); // preferred way of calling C++17
        entity->PrintSomething();

        std::shared_ptr<Entity> e0;
        {
            std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();

            e0=sharedEntity; // increase refcount
            std::weak_ptr<Entity> weakEntity = sharedEntity; // does not increase refcount
            
            sharedEntity->PrintSomething();
        }
        e0->PrintSomething();
    }
    /* weak_ptr does not increase the ref count
    priorty to use:
    1: use unique_ptr
    2. use shared_ptr */
    return 0;
}