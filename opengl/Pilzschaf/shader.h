#pragma once
#include "defines.h"
#include <string>
#include <GL/glew.h>

class Shader{
    private:
        GLuint shaderId;
        GLuint compile(std::string shaderSource, GLenum type);
        std::string parse(const char* filename);
        GLuint createShader(const char* vertexShaderFilename, const char* fragmentShaderFilename);
    
    public:
        Shader(const char* vertexShaderFilename, const char* fragementShaderFilename);
        virtual ~Shader();
        GLuint getShaderId();
        void bind();
        void unbind();
    
};