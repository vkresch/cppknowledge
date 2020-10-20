// https://www.youtube.com/watch?v=6uqU9Y578n4&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=67
// Unions
// Unions are like struct types but they only occupy memory of one member at a time
// When we have a struct with four ints we store 4x4=16 Bytes
// A union can have only one member even if I declare 4 members = 4 Bytes
#include <iostream>

struct Vector2 {
    float x, y;
};

// struct Vector4 {
//     float x, y, z, w;

//     Vector2& GetA(){
//         return *(Vector2*)&x;
//     }
// };

struct Vector4 {
    union {
        struct {
            float x, y, z, w;
        };
        struct {
            Vector2 a, b;
        };
    };
};

void PrintVector2(const Vector2& vector){
    std::cout << vector.x << ", " << vector.y << std::endl;
}

int main(){
    // Anonymous union
    struct Union {
        union {
            float a;
            int b;
        };
    };

    Union u;
    u.a = 2.0f;
    // u.b is a int representation of the float
    // u.b is type punned
    std::cout << u.a << ", " << u.b << std::endl;

    // More usefule example
    Vector4 vector = {1.0f, 2.0f, 3.0f, 4.0f};
    PrintVector2(vector.a);
    PrintVector2(vector.b);
    std::cout << "-----------" << std::endl;

    // Change the z value
    vector.z = 500.0f;
    PrintVector2(vector.b);
    return 0;
}