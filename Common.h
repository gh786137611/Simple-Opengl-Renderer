//
// Created by mm on 2019/11/19.
//

#ifndef SGLRENDER_COMMON_H
#define SGLRENDER_COMMON_H

#include <memory>
#include <cassert>
#include <iostream>
#include <functional>
#include <functional>
#include <map>
#include <string>
#include <string.h>
#include <array>
#include <list>
#include <vector>

#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#ifndef SGL_BEGIN
#define SGL_BEGIN namespace SGL{
#endif

#ifndef SGL_END
#define SGL_END }
#endif


SGL_BEGIN


enum  TextureParameter {
    Linear = GL_LINEAR,
    Nearest = GL_NEAREST,
    Repeat = GL_REPEAT,
    Clamp = GL_CLAMP,
    ClampToEdge = GL_CLAMP_TO_EDGE,
    LinearMipMapLinear = GL_LINEAR_MIPMAP_LINEAR,
    LinearMipMapNearest = GL_LINEAR_MIPMAP_NEAREST,
    NearestMipMapLinear = GL_NEAREST_MIPMAP_LINEAR,
    NearestMipMapNearest = GL_NEAREST_MIPMAP_NEAREST
};

enum  PixelFormat {
    RGBA = GL_RGBA,
    RGB = GL_RGB,
    Red = GL_RED
};

enum class Face {
    Front = GL_FRONT,
    Back = GL_BACK,
    FrontBack = GL_FRONT_AND_BACK,
    None
};

enum class PolygonMode{
    Fill = GL_FILL,
    Line = GL_LINE
};

int ChannelOfPixelFormat(PixelFormat format);

enum  TextureDataType {
    UBYTE = GL_UNSIGNED_BYTE,
    BYTE = GL_BYTE,
    Float = GL_FLOAT
};

int SizeOfTextureDataType(TextureDataType type);

void PrintGLError(int error);





class VertexBuffer;
class IndexBuffer;
class Geometry;
class ShaderMaterial;
class Attrib;
class Shader;
class Uniform;
class UniformValue;
class Object3D;
class TriMesh;
class Point;
class Camera;
class PerspectiveCamera;
class Texture;
class Texture2D;
class TextureCube;
class Scene;
class Line;
using std::cout;
using std::endl;
SGL_END



#endif //SGLRENDER_COMMON_H
