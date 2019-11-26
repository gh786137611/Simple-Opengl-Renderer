//
// Created by mm on 2019/11/19.
//

#ifndef SGLRENDER_UNIFORM_H
#define SGLRENDER_UNIFORM_H

#include "Common.h"

SGL_BEGIN

class Uniform {
public:
    Uniform(unsigned loc, unsigned size, const std::string & name, unsigned textreUnit = 0) {
        m_location = loc;
        m_name = name;
        m_textureUnit = textreUnit;
        m_size = size;
    }
public:
    unsigned m_location;
    int m_textureUnit;
    std::string m_name;
    unsigned m_size;
};


SGL_END
#endif //SGLRENDER_UNIFORM_H
