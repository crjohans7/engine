#include "terrain.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Terrain::Terrain(const char* terrainFilepath)
{
    int width, height, numChannels;
    unsigned char* data = stbi_load(terrainFilepath, &width, &height, &numChannels, 0);
    
}