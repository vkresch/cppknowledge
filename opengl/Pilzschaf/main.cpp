#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#define GLEW_STATIC
#include <GL/glew.h>
#define SDL_MAIN_HANDLED

#define STB_IMAGE_IMPLEMENTATION
#include "libs/stb_image.h"

#include "libs/glm/glm.hpp"
#include "libs/glm/ext/matrix_transform.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"

#ifdef _WIN32
#include <SDL.h>
#pragma comment(lib, "SDL2.llib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")
#else
#include <SDL2/SDL.h>
#endif

#include "defines.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "shader.h"
#include "floating_camera.h"
#include "mesh.h"

// Function to handle error exceptions
void openGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam){
    std::cout << "[OpenGL Error]: " << message << std::endl;
}

int main(int argc, char** argv){
    SDL_Window* window;
    SDL_Init(SDL_INIT_EVERYTHING);

    // Set the bit size for the colors explicit
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); // not mandatory but for explicitly
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetSwapInterval(-1);

    #ifdef _DEBUG
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    #endif

    uint32 flags = SDL_WINDOW_OPENGL; // SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP

    window = SDL_CreateWindow("C++ OpenGL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, flags);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    // Initialisiere GLEW
    GLenum err = glewInit();
    if(err!=GLEW_OK){
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
        std::cin.get();
        return -1;
    }
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    #ifdef _DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(openGLDebugCallback, 0);
    #endif

    Shader shader("shaders/basic.vs", "shaders/basic.fs");
    shader.bind();

    int directionLocation = glGetUniformLocation(shader.getShaderId(), "u_directional_light.direction");
    glm::vec3 sunColor = glm::vec3(0.0f);
    glm::vec3 sunDirection = glm::vec3(-1.0f);
    glUniform3fv(glGetUniformLocation(shader.getShaderId(), "u_directional_light.diffuse"), 1, (float*)&sunColor.x);
    glUniform3fv(glGetUniformLocation(shader.getShaderId(), "u_directional_light.specular"), 1, (float*)&sunColor.x);
    sunColor *= 0.4f; // Etwas schwächeres ambient light erzeugen, sonst sehr merkwürdig
    glUniform3fv(glGetUniformLocation(shader.getShaderId(), "u_directional_light.ambient"), 1, (float*)&sunColor.x);

    // Define the point light
    glm::vec3 pointLightColor = glm::vec3(0.0f, 0.0f, 0.0f);
    glUniform3fv(glGetUniformLocation(shader.getShaderId(), "u_point_light.diffuse"), 1, (float*)&pointLightColor.x);
    glUniform3fv(glGetUniformLocation(shader.getShaderId(), "u_point_light.specular"), 1, (float*)&pointLightColor.x);
    pointLightColor *= 0.2f; // Etwas schwächeres ambient light erzeugen, sonst sehr merkwürdig
    glUniform3fv(glGetUniformLocation(shader.getShaderId(), "u_point_light.ambient"), 1, (float*)&pointLightColor.x);

    // http://wiki.ogre3d.org/-Point+Light+Attenuation
    glUniform1f(glGetUniformLocation(shader.getShaderId(), "u_point_light.linear"), 0.027f);
    glUniform1f(glGetUniformLocation(shader.getShaderId(), "u_point_light.quadratic"), 0.0028f);    

    //vec4 da später mit Matrix verrechnet wird
    glm::vec4 pointLightPosition = glm::vec4(0.0f, 0.0f, 10.0f, 1.0f);
    int positionLocation = glGetUniformLocation(shader.getShaderId(), "u_point_light.position");

    // Spotlight
    glm::vec3 spotLightColor = glm::vec3(1.0f);
    glUniform3fv(glGetUniformLocation(shader.getShaderId(), "u_spot_light.diffuse"), 1, (float*)&spotLightColor.x);
    glUniform3fv(glGetUniformLocation(shader.getShaderId(), "u_spot_light.specular"), 1, (float*)&spotLightColor.x);
    spotLightColor *= 0.2f; // Etwas schwächeres ambient light erzeugen, sonst sehr merkwürdig
    glUniform3fv(glGetUniformLocation(shader.getShaderId(), "u_spot_light.ambient"), 1, (float*)&spotLightColor.x);
    glm::vec3 spotLightPosition = glm::vec3(0.0f);
    glUniform3fv(glGetUniformLocation(shader.getShaderId(), "u_spot_light.position"), 1, (float*)&spotLightPosition.x);
    spotLightPosition.z = 1.0f; // Richtung bewegt sich immer Richtung z achse
    glUniform3fv(glGetUniformLocation(shader.getShaderId(), "u_spot_light.direction"), 1, (float*)&spotLightPosition.z);

    glUniform1f(glGetUniformLocation(shader.getShaderId(), "u_spot_light.innerCone"), 0.95f);
	glUniform1f(glGetUniformLocation(shader.getShaderId(), "u_spot_light.outerCone"), 0.80f);

    // Load the monkey model
    Model monkey;
    monkey.init("models/fern.bmf", &shader);

    uint64 prefCounterFrequency = SDL_GetPerformanceFrequency();
    uint64 lastCounter = SDL_GetPerformanceCounter();
    float32 delta = 0.0f;

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Switch to wireframe modus

    // Create a model matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(0.1f)); // Scale in .fbx files works different thant in .obj

    FloatingCamera camera(90.0f, 800.0f, 600.0f);
    camera.translate(glm::vec3(0.0f, 0.0f, 5.0f));
    camera.update();

    // bool orthomode = false;
    // glm::mat4 ortho = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -10.0f, 100.0f);
    // glm::mat4 perspective = glm::perspective(glm::radians(45.0f), 4.0f/3.0f, 0.1f, 100.0f); // Field of View
    // glm::mat4 projection = perspective;

    // // add camera view matrix
    // glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));

    glm::mat4 modelViewProj = camera.getViewProj() * model;

    int modelViewProjMatrixLocation = glGetUniformLocation(shader.getShaderId(), "u_modelViewProj"); 
    int modelViewLocation = glGetUniformLocation(shader.getShaderId(), "u_modelView");
    int invModelViewLocation = glGetUniformLocation(shader.getShaderId(), "u_invModelView");

    float time = 0.0f;
    bool close = false;

    // button defintions
    bool buttonW = false;
    bool buttonA = false;
    bool buttonS = false;
    bool buttonD = false;
    bool buttonSpace = false;
    bool buttonShift = false;

    float cameraSpeed = 6.0f;
    SDL_SetRelativeMouseMode(SDL_TRUE); // Set relative mouse mode
    glEnable(GL_CULL_FACE); // Do not draw triangle which are not visisble to the camera
    // glFrontFace(GL_CCW); // Show triangles in counter clock wise (ccw) manner 
    glEnable(GL_DEPTH_TEST);
    while(!close){

        SDL_GL_SwapWindow(window); 
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                close = true;
            } else if(event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym){
                    case SDLK_w:
                        buttonW = true;
                        break;
                    case SDLK_a:
                        buttonA = true;
                        break;
                    case SDLK_s:
                        buttonS = true;
                        break;
                    case SDLK_d:
                        buttonD = true;
                        break;
                    case SDLK_SPACE:
                        buttonSpace = true;
                        break;
                    case SDLK_LSHIFT:
                        buttonShift = true;
                        break;
                    case SDLK_ESCAPE:
                        SDL_SetRelativeMouseMode(SDL_FALSE);
                        break;

                    // case SDLK_p:
                    //     if(orthomode){
                    //         projection = perspective;
                    //     } else {
                    //         projection = ortho;
                    //     }
                    //     orthomode = !orthomode;
                    //     break;
                    
                }
            } else if(event.type == SDL_KEYUP){
                switch (event.key.keysym.sym){
                    case SDLK_w:
                        buttonW = false;
                        break;
                    case SDLK_a:
                        buttonA = false;
                        break;
                    case SDLK_s:
                        buttonS = false;
                        break;
                    case SDLK_d:
                        buttonD = false;
                        break;
                    case SDLK_SPACE:
                        buttonSpace = false;
                        break;
                    case SDLK_LSHIFT:
                        buttonShift = false;
                        break;
                }
            } else if(event.type == SDL_MOUSEMOTION){
                if(SDL_GetRelativeMouseMode()){
                    camera.onMouseMove(event.motion.xrel, event.motion.yrel);
                }
            } else if(event.type == SDL_MOUSEBUTTONDOWN){
                if(event.button.button == SDL_BUTTON_LEFT){
                    SDL_SetRelativeMouseMode(SDL_TRUE);
                }
            }
        }

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the depth buffer for better visualization
        time += delta;

        if(buttonW){
            camera.moveFront(delta * cameraSpeed);
        }
        if(buttonA){
            camera.moveSideways(-delta * cameraSpeed);
        }
        if(buttonS){
            camera.moveFront(-delta * cameraSpeed);
        }
        if(buttonD){
            camera.moveSideways(delta * cameraSpeed);
        }
        if(buttonSpace){
            camera.moveUp(delta * cameraSpeed);
        }
        if(buttonShift){
            camera.moveUp(-delta * cameraSpeed);
        }     
        camera.update();

        model = glm::rotate(model, 1.0f * delta, glm::vec3(1, 1, 1));
        // model = glm::mat4(1.0f);
        // model = glm::scale(model, glm::vec3(sinf(time), 1, 1));
        glm::mat4 modelViewProj = camera.getViewProj() * model;

        glm::mat4 modelView = camera.getView() * model;
        glm::mat4 invModelView = glm::transpose(glm::inverse(modelView));
        glm::vec4 transformedSunDirection = glm::transpose(glm::inverse(camera.getView())) * glm::vec4(sunDirection, 1.0f);
        glUniform3fv(directionLocation, 1,  (float*)&transformedSunDirection.x);

        glm::mat4 pointLightMatrix = glm::rotate(glm::mat4(1.0f), -delta, {0.0f, 1.0f, 0.0f});
        pointLightPosition = pointLightMatrix * pointLightPosition;
        glm::vec3 transformedPointLightPosition = (glm::vec3)(camera.getView() * pointLightPosition);
        glUniform3fv(positionLocation, 1, (float*)&transformedPointLightPosition.x);

        glUniformMatrix4fv(modelViewProjMatrixLocation, 1, GL_FALSE, &modelViewProj[0][0]);
        glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, &modelView[0][0]);
        glUniformMatrix4fv(invModelViewLocation, 1, GL_FALSE, &invModelView[0][0]);
        monkey.render();

        // Calculate the FPS
        uint64 endCounter = SDL_GetPerformanceCounter();
        uint64 counterElapsed = endCounter - lastCounter;
        delta = ((float32)counterElapsed) / ((float32)prefCounterFrequency);
        uint32 FPS = (uint32)((float32)prefCounterFrequency) / (float32)counterElapsed;
        // std::cout << "FPS: " << FPS << std::endl;
        lastCounter = endCounter;
    }

    return 0;
}