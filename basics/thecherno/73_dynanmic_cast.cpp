#include <iostream>
#include <string>

class Entity {
    public:
    virtual void PrintName(){}
};

class Player : public Entity {
};

class Enemy : public Entity {
};

int main(){
    Player* player = new Player();
    Entity* actually_enemy = new Enemy();    
    Entity* actually_player = player;

    Player* p0 = (Player*)actually_enemy; // Dangerous stuff !!!!!
    // When we try access stuff which enemy does not have the code will break

    Player* p1 = dynamic_cast<Player*>(actually_enemy);
    if(!p1){
        std::cout << "Player does not exist!" << std::endl;
    }
    Player* p2 = dynamic_cast<Player*>(actually_player);
    // C++ stores runtime type information (RTTI) thats how it knows
    // dynamic_cast performs a check
    // These add overhead to your program

    return 0;
}