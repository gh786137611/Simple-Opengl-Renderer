cmake_minimum_required(VERSION 2.8)
project(SGLRender)

set(CMAKE_CXX_STANDARD 11)

add_executable(SGLRender main.cpp VertexBuffer.cpp VertexBuffer.h Common.h Common.cpp IndexBuffer.cpp IndexBuffer.h Geometry.cpp Geometry.h ShaderMaterial.cpp ShaderMaterial.h Attrib.cpp Attrib.h Shader.cpp Shader.h Uniform.cpp Uniform.h TriMesh.cpp TriMesh.h Camera.cpp Camera.h Texture.cpp Texture.h Common.cpp SGL.h stb_image.cpp Object3D.cpp Object3D.h UniformValue.cpp UniformValue.h Scene.cpp Scene.h Line.cpp Line.h)


target_link_libraries(SGLRender GLEW GL glut)
