// https://www.youtube.com/watch?v=gNgUMA_Ur0U&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=64
// Multidimensional Array
#include <iostream>

int main(){
    // Integer size is 4 Bytes
    int* array = new int[50]; // 50 * 4 Bytes = 200 Bytes of memory allocation

    int** array_2d = new int*[50];

    // Initialize in each array address an actual array
    for(int i = 0; i < 50; i++){
        array_2d[i] = new int[50];
    }

    // How to set up a 3d arrays
    int*** a3d = new int**[50];
    for(int i = 0; i < 50; i++){
        a3d[i] = new int*[50];
        for(int j=0; j < 50; j++){
            a3d[i][j] = new int[50];
        }
    }

    // Deleting multidimensional array
    // 2d way
    for(int i=0; i < 50; i++){
            delete[] array_2d[i];
        }
    delete[] array_2d; 

    /*
    Note:
    - downside of 2d arrays is that they are scattered accross memory
    - one could also use a 1d array of size 50 * 50 instead if 2d [50][50] array
    - 2d arrays are slower than 1d arrays to iterate over  
    - you can always replace a 2d array with a 1d array
    - avoid 2d arrays as much as possible
    */

    // using 1d array instead of 2d array
    // how you normally set up in a 2d array
    int** array_2d = new int*[5];
    for(int y = 0; y < 5; y++){
        for(int x = 0; x < 5; x++){
            array_2d[y][x] = 0;
        }
    }

    // how to equivalently set up in a 1d array
    int* array_1d = new int[5*5];
    for(int k = 0; k < 5*5; k++){
        array_1d[k] = 0;
    }

    // This way like above in 2d is also possible to write
    // Efficient and looks like the 2d version
    for(int y = 0; y < 5; y++){
        for(int x = 0; x < 5; x++){
            array_1d[x + y * 5] = 0;
        }
    }

    return 0;
}