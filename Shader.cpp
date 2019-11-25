//
// Created by mm on 2019/11/19.
//

#include "Shader.h"
#include "Attrib.h"
#include "Uniform.h"
#include <iostream>


SGL_BEGIN

Shader::Shader(const std::string &vert, const std::string &frag) {
    m_vert = vert;
    m_frag = frag;
    m_program = 0;
}

void Shader::get_active_attribs() {
    int num = 0;
    int length;
    char name[512];
    int size;
    GLenum  type;
    glGetProgramiv(m_program, GL_ACTIVE_ATTRIBUTES, &num);
    for (int i=0; i<num; ++i) {
        glGetActiveAttrib(m_program, i, 512, &length, &size, &type, name);
        unsigned loc = glGetAttribLocation(m_program, name);
        m_attribs.push_back(Attrib(loc,
                                       Attrib::component_size(type),
                                       Attrib::component_type(type), name));
    }
}


static const char * type_to_name(unsigned type) {
#define iterm(x) case x : return #x
    switch (type){
        iterm(GL_FLOAT);
        iterm(GL_FLOAT_VEC2);
        iterm(GL_FLOAT_VEC3);
        iterm(GL_FLOAT_VEC4);
        iterm(GL_FLOAT_MAT2);
        iterm(GL_FLOAT_MAT3);
        iterm(GL_FLOAT_MAT4);
        iterm(GL_SAMPLER_2D);
        iterm(GL_SAMPLER_CUBE);
    }
#undef iterm
    return "unknown";
}

void Shader::get_active_uniforms() {
    int num = 0;
    int length;
    char name[512];
    int size;
    GLenum  type;
    glGetProgramiv(m_program, GL_ACTIVE_UNIFORMS, &num);
    int samplerNum = 0;
    for (int i= 0; i<num; ++i){
        glGetActiveUniform(m_program, i, 512, &length, &size, &type, name);
        //cout << "name: " << name << ", size: " << size <<", type: " <<  type_to_name(type)<<endl;
        Uniform uniform = Uniform(glGetUniformLocation(m_program, name),size, name, -1);
        if (is_sampler(type)) {
            uniform.m_textureUnit = samplerNum;
            samplerNum++;
        }
        m_uniforms.push_back(uniform);
    }
}

bool Shader::is_sampler(unsigned type) {
    return type == GL_SAMPLER_2D  ||
           type == GL_SAMPLER_1D ||
           type == GL_SAMPLER_3D ||
           type == GL_SAMPLER_CUBE;
}



Shader::~Shader() {
    m_attribs.clear();
    m_uniforms.clear();
}


std::shared_ptr<Shader> Shader::create(const std::string &vert, const std::string &frag) {
    return std::shared_ptr<Shader>(new Shader(vert, frag));
}

void Shader::bind() {
    if (0 != m_program) {
        glUseProgram(m_program);
    }else{
        unsigned vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        {
            const std::string & source = m_vert;
            const char * p = source.c_str();
            glShaderSource(vertex_shader, 1, &p, nullptr);
            glCompileShader(vertex_shader);
            int status;
            glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
            if (!status) {
                char log[512];
                int length;
                glGetShaderInfoLog(vertex_shader, 511, &length, log);
                log[511] = 0;
                std::cout << log<<std::endl;
                return;
            }
        }

        unsigned frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
        {
            const std::string &source = m_frag;
            const char * p = source.c_str();
            glShaderSource(frag_shader, 1, &p, nullptr);
            glCompileShader(frag_shader);
            int status;
            glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &status);
            if (!status) {
                char log[512];
                int length;
                glGetShaderInfoLog(frag_shader, 511, &length, log);
                log[511] = 0;
                std::cout << log<<std::endl;
                return;
            }
        }

        m_program = glCreateProgram();
        glAttachShader(m_program, vertex_shader);
        glAttachShader(m_program, frag_shader);
        glLinkProgram(m_program);
        glDeleteShader(vertex_shader);
        glDeleteShader(frag_shader);

        get_active_attribs();
        get_active_uniforms();
        glUseProgram(m_program);
    }
}

SGL_END