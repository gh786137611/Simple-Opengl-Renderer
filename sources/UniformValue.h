//
// Created by mm on 2019/11/22.
//

#ifndef SGLRENDER_UNIFORMVALUE_H
#define SGLRENDER_UNIFORMVALUE_H

#include "Common.h"
#include "Uniform.h"
SGL_BEGIN

class UniformValue {
    friend ShaderMaterial;
public:
    virtual void bind(Uniform * u) = 0;
    virtual ~UniformValue(){}
};

template <typename _T>
class UniformValueT: public UniformValue{
public:
    void bind(Uniform * u) override {
        assert(false);
    }
    UniformValueT(const _T &t):m_data(t){

    }
    void set_data(const _T &t){
        m_data = t;
    }
private:
    _T m_data;
};

template <>
void UniformValueT<float>::bind(Uniform *u);

template <>
void UniformValueT<glm::vec2>::bind(Uniform *u);

template <>
void UniformValueT<glm::vec3>::bind(Uniform *u);

template <>
void UniformValueT<glm::vec4>::bind(Uniform *u);

template <>
void UniformValueT<glm::mat2>::bind(Uniform *u);

template <>
void UniformValueT<glm::mat3>::bind(Uniform *u);

template <>
void UniformValueT<glm::mat4>::bind(Uniform *u);

template <>
void UniformValueT<std::vector<glm::vec2>>::bind(Uniform *u);

template <>
void UniformValueT<std::vector<glm::vec3>>::bind(Uniform *u);

template <>
void UniformValueT<std::vector<glm::vec4>>::bind(Uniform *u);

SGL_END
#endif //SGLRENDER_UNIFORMVALUE_H

