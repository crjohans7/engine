#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>

class Shader
{
private:
    unsigned int id;

public:
    Shader(std::string vertexFilePath, std::string fragmentFilePath);
    ~Shader();
    void bind();
    void unbind();
    unsigned int getId();
    unsigned int loadShader(std::string filepath, unsigned int type);
};

#endif