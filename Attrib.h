//
// Created by mm on 2019/11/19.
//

#ifndef SGLRENDER_ATTRIB_H
#define SGLRENDER_ATTRIB_H

#include "Common.h"

SGL_BEGIN

class Attrib {
    friend Shader;
    friend VertexBuffer;
    friend  ShaderMaterial;
private:
    Attrib(unsigned location, unsigned size, unsigned type, const std::string &name);
    static unsigned component_size(unsigned type);
    static unsigned component_type(unsigned type);
private:
    std::string m_name;
    unsigned m_location;
    unsigned m_size;
    unsigned m_type;
};

SGL_END
#endif //SGLRENDER_ATTRIB_H
