# Render Engine

Ongoing solo project to create a render engine with OpenGL, GLFW, stb_image.

## How to run

Requirements: CMake version 4.0+, OpenGL 4.1+, C++11
```
mkdir build
cd build
cmake ..
make
./render_engine
```

## Roadmap

Camera manager class (right now can toggle between two cameras with 'W')

UI component to manage cameras

Terrain class using height map images, separate into patches for LOD 

Mesh loader (assimp lib)

Materials

Entity and Transform class

Scene/SceneMangager class

Skybox/skydome

more...

