//
// Created by mm on 2019/11/19.
//

#include "Attrib.h"
#include "VertexBuffer.h"

SGL_BEGIN

Attrib::Attrib(unsigned location, unsigned size, unsigned type, const std::string &name) {
    m_location = location;
    m_size = size;
    m_type = type;
    m_name = name;
}

unsigned Attrib::component_size(unsigned type) {
    switch (type){
        case GL_FLOAT:
            return 1;
        case GL_FLOAT_VEC2:
            return 2;
        case GL_FLOAT_VEC3:
            return 3;
        case GL_FLOAT_VEC4:
            return 4;
        default:
            assert(false);
            break;
    }
    return 0;
}

unsigned Attrib::component_type(unsigned type) {
    switch (type){
        case GL_FLOAT:
        case GL_FLOAT_VEC2:
        case GL_FLOAT_VEC3:
        case GL_FLOAT_VEC4:
            return GL_FLOAT;
        default:
            assert(false);
            break;
    }
    return 0;
}

SGL_END
