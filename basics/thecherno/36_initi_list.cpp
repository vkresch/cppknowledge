#include <iostream>

class Entity {
    public:
        Entity(float x, float y){
            X = x;
            Y = y;
        }
        float X, Y;

        void Move(float xa, float ya){
            X += xa;
            Y += ya;
        }

        void PrintPos(){
            std::cout << "X: " << X << " Y: " << Y << std::endl;
        }
};

class Player : public Entity {
    public:
        Player(const char* name, float x, float y) : Entity(x, y){
            Name = name;            
        }
        const char* Name;

        void PrintName(){
            std::cout << Name << std::endl;
        }
};

int main(){
    Player e("Viktor Kreschenski", 12.0f, 32.0f);
    e.PrintName();
    return 0;
}