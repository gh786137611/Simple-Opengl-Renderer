//
// Created by mm on 2019/11/19.
//

#ifndef SGLRENDER_SHADER_H
#define SGLRENDER_SHADER_H

#include "Common.h"
SGL_BEGIN

class Shader {
    friend Object3D;
    friend  ShaderMaterial;
public:
    static Ptr<Shader> create(const std::string & vert, const std::string & frag);
    ~Shader();
private:
    Shader(const std::string & vert, const std::string & frag);
    void get_active_attribs();
    void get_active_uniforms();
    static bool is_sampler(unsigned type);
    void bind();
private:
    unsigned m_program;
    std::vector<Attrib> m_attribs;
    std::vector<Uniform> m_uniforms;
    std::string m_vert;
    std::string m_frag;
};

SGL_END
#endif //SGLRENDER_SHADER_H
