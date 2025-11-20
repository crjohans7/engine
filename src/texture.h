#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

class Texture
{
private:
    unsigned int id;

public:
    Texture(const char* textureFilePath);
    ~Texture();
    unsigned int getId();
};

#endif