# movingMeshR3

This project involves developing a C++ game that utilizes OpenGL, GLFW, and GLM to move spaceships from one hangar to another.

## Features:
* Loading objects into the game, such as hangars and Star Wars inspired ships.
* Implementing lighting in the scene to enhance realism.


## To compile:
  g++ main.cpp shader.cpp objloader.cpp texture.cpp -o main -lglfw -lGLEW -lGL -lX11 -lpthread -lXrandr -ldl
