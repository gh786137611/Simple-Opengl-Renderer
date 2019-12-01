# SGLRenderer: A Simple and easy-to-use OpenGL Renderer based on C++ language

This is a simple OpenGL-based Renderer for my graphics research application. 
It wraps the GLSL-based Shader to allow quick 3D rendering demostration.
GLM(https://github.com/g-truc/glm) is used for matrix calculation.


## Features
+ Simple: No rendering algorithm is included. You must write yours.
+ All the GPU Buffers are allocated at their first usage in rendering.

## Usage
There are simple examples. I take freeglut as window system in my examples. To use SGLRenderer there are three main steps:
1. Writing you glsl-based shader
2. initialize Geometry and ShaderMaterial to create a 3D object
3. add the 3D object to a Scene.

You must combine the SGLRenderer code with your window system. I think the combination is easy, 
which only involves initialization and draw code block in Qt and freeglut.
