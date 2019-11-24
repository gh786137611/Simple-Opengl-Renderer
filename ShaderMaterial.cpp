//
// Created by mm on 2019/11/19.
//

#include "ShaderMaterial.h"
#include "Uniform.h"
#include "Shader.h"
#include "Geometry.h"
#include "Attrib.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include <string>
#include <string.h>

SGL_BEGIN

ShaderMaterial::ShaderMaterial(std::shared_ptr<Shader> & shader) {
    m_shader = shader;
    m_blend = [](){
        glDisable(GL_BLEND);
    };
    m_depthTest = [](){
        glEnable(GL_DEPTH_TEST);
    };
}


void ShaderMaterial::set_texture(const std::string &name, std::shared_ptr<Texture> &texture) {
    m_textures[name] = texture;
}

std::shared_ptr<Texture> ShaderMaterial::get_texture(const std::string &name) {
    auto it = m_textures.find(name);
    if (it != m_textures.end()) {
        return it->second;
    }else{
        return std::shared_ptr<Texture>{};
    }
}

ShaderMaterial::~ShaderMaterial() {
    for (auto u: m_uniformValue) {
        delete u.second;
    }
    m_uniformValue.clear();
}

std::shared_ptr<ShaderMaterial> ShaderMaterial::create(std::shared_ptr<Shader> & shader) {
    return std::shared_ptr<ShaderMaterial>(new ShaderMaterial(shader));
}

void ShaderMaterial::bind_uniforms() {
    for (Uniform & u : m_shader->m_uniforms) {
        if (u.m_textureUnit <0) {
            auto it = m_uniformValue.find(u.m_name);
            if (it != m_uniformValue.end()) {
                it->second->bind(&u);
            }
        } else{ // uniform for sampler
            std::map<std::string, std::shared_ptr<Texture>>::iterator it = m_textures.find(u.m_name);
            if (it != m_textures.end()){
                it->second->bind(u.m_textureUnit);
            }
        }
    }
}


void ShaderMaterial::bind(std::shared_ptr<Geometry> &g) {
    m_shader->bind();

    state_switch();

    bind_uniforms();
    for (Attrib &a : m_shader->m_attribs) {
        std::shared_ptr<VertexBuffer> vbo = g->get_attribute(a.m_name);
        vbo->bind(&a);
    }
}

void ShaderMaterial::state_switch() {
    m_blend();
    m_depthTest();
}

SGL_END