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

## Previous Renders

<img width="2880" height="1800" alt="01" src="https://github.com/user-attachments/assets/78fcccc7-57e5-4a87-9a56-1af260744303" />

<img width="2880" height="1800" alt="02" src="https://github.com/user-attachments/assets/d138f78a-459e-4643-9a5f-a8f46c6c7ef7" />
