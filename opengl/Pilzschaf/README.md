# Cook list OpenGL

## Preparation

## Simple compile and run
```bash
g++ -g -std=c++11 main.cpp -o main -lGL -lSDL2 -lGLEW && ./main
```
## Shaders
Shaders are just programs which run on the gpu.

## Export model into custom binary format

Compile/Run it with:
```bash
g++ -std=c++11 modelexporter.cpp -lassimp -o modelexporter
./modelexporter models/cube.obj 
```