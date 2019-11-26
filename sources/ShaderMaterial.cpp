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

ShaderMaterial::ShaderMaterial(Ptr<Shader> & shader) {
    m_shader = shader;
    set_depthTest(true);
    set_blend(false);
}


void ShaderMaterial::set_texture(const std::string &name, Ptr<Texture> texture) {
    m_textures[name] = texture;
}

Ptr<Texture> ShaderMaterial::get_texture(const std::string &name) {
    auto it = m_textures.find(name);
    if (it != m_textures.end()) {
        return it->second;
    }else{
        return Ptr<Texture>{};
    }
}

ShaderMaterial::~ShaderMaterial() {
    for (auto u: m_uniformValue) {
        delete u.second;
    }
    m_uniformValue.clear();
}

Ptr<ShaderMaterial> ShaderMaterial::create(Ptr<Shader> & shader) {
    return Ptr<ShaderMaterial>(new ShaderMaterial(shader));
}

void ShaderMaterial::bind_uniforms() {
    for (Uniform & u : m_shader->m_uniforms) {
        if (u.m_textureUnit <0) {
            auto it = m_uniformValue.find(u.m_name);
            if (it != m_uniformValue.end()) {
                it->second->bind(&u);
            }
        } else{ // uniform for sampler
            std::map<std::string, Ptr<Texture>>::iterator it = m_textures.find(u.m_name);
            if (it != m_textures.end()){
                it->second->bind(&u);
            }
        }
    }
}


void ShaderMaterial::bind(Ptr<Geometry> &g) {
    m_shader->bind();

    state_switch();

    bind_uniforms();
    for (Attrib &a : m_shader->m_attribs) {
        Ptr<VertexBuffer> vbo = g->get_attribute(a.m_name);
        vbo->bind(&a);
    }
}

void ShaderMaterial::state_switch() {
    m_blend();
    m_depthTest();
}

SGL_END