#include "shader.h"
#include <fstream>
#include <sstream>

Shader::Shader(std::string vertexFilePath, std::string fragmentFilePath)
{
    // Link vertex & fragment shaders
    unsigned int vertexShader, fragmentShader;
    vertexShader = loadShader(vertexFilePath, GL_VERTEX_SHADER);
    fragmentShader = loadShader(fragmentFilePath, GL_FRAGMENT_SHADER);
    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);
    // Link check
    int  success;
    char infoLog[512];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        fprintf(stderr, "\nError: %s\n\n", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(id);
}

void Shader::bind()
{
    // Use shader program
    glUseProgram(id);
}

void Shader::unbind()
{
    glUseProgram(0);
}

unsigned int Shader::getId()
{
    return id;
}

unsigned int Shader::loadShader(std::string filepath, unsigned int type)
{
    // Read file
    std::fstream file;
    file.open(filepath);
    std::string line;
    std::stringstream bufferedLines;
    while (std::getline(file, line))
    {
        bufferedLines << line << "\n";
    }
    std::string entireStr = bufferedLines.str();
    const char* shaderSource = entireStr.c_str(); // Need '\0' terminated string for shader
    bufferedLines.str("");
    file.close();

    // Compile shader based on type
    unsigned int shader;
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    // Compile check
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        fprintf(stderr, "\nError: %s\n\n", infoLog);
    }

    return shader;
}

