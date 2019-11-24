//
// Created by mm on 2019/11/19.
//

#ifndef SGLRENDER_SHADERMATERIAL_H
#define SGLRENDER_SHADERMATERIAL_H

#include "Common.h"
#include "UniformValue.h"
SGL_BEGIN

class ShaderMaterial {
    friend TriMesh;
    friend Line;
public:
    void set_texture(const std::string &name, std::shared_ptr<Texture> & texture);
    static std::shared_ptr<ShaderMaterial> create(std::shared_ptr<Shader> & shader);
    std::shared_ptr<Texture> get_texture(const std::string & name);
    ~ShaderMaterial();
    template <typename _T>
    void set_value(const std::string &name, const _T & t) {
        auto it = m_uniformValue.find(name);
        if (it != m_uniformValue.end()) {
            UniformValueT<_T> * uv = dynamic_cast<UniformValueT<_T> *>(it->second);
            if (uv) {
                uv->set_data(t);
            }else{
                delete it->second;
                it->second =  new UniformValueT<_T>(t);;
            }
        }else{
            m_uniformValue[name] =  new UniformValueT<_T>(t);
        }
    }

    void set_blend(bool blending){
        if (blending) {
            m_blend = []() {
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            };
        }else{
            m_blend = []() {
                glDisable(GL_BLEND);
            };
        }
    }
    void set_depthTest(bool depthTest){
        if (depthTest) {
            m_depthTest = []() {
                glDisable(GL_DEPTH_TEST);
            };
        }else{
            m_depthTest =  []() {
                glEnable(GL_DEPTH_TEST);
                glDepthFunc(GL_LESS);
            };
        }
    }
protected:
    ShaderMaterial(std::shared_ptr<Shader>& shader);
    void bind(std::shared_ptr<Geometry> & g);
    void bind_uniforms();
    void state_switch();
protected:
    std::shared_ptr<Shader> m_shader;
    std::map<std::string, std::shared_ptr<Texture>> m_textures;
    std::map<std::string, UniformValue *> m_uniformValue;
protected:
    std::function<void(void)> m_blend;
    std::function<void(void)> m_depthTest;
};

SGL_END
#endif //SGLRENDER_SHADERMATERIAL_H
