//
// Created by mm on 2019/11/22.
//

#include "UniformValue.h"

SGL_BEGIN


template <>
void UniformValueT<float>::bind(Uniform *u) {
    assert(u->m_size == 1);
    glUniform1fv(u->m_location, 1, &m_data);
}


template <>
void UniformValueT<glm::vec2>::bind(Uniform *u) {
    assert(u->m_size == 1);
    glUniform2fv(u->m_location, 1, &m_data[0]);
}

template <>
void UniformValueT<glm::vec3>::bind(Uniform *u) {
    assert(u->m_size == 1);
    glUniform3fv(u->m_location, 1, &m_data[0]);
}

template <>
void UniformValueT<glm::vec4>::bind(Uniform *u) {
    assert(u->m_size == 1);
    glUniform4fv(u->m_location, 1, &m_data[0]);
}

template <>
void UniformValueT<glm::mat2>::bind(Uniform *u) {
    assert(u->m_size == 1);
    glUniformMatrix2fv(u->m_location, 1, GL_FALSE, &m_data[0][0]);
}
template <>
void UniformValueT<glm::mat3>::bind(Uniform *u) {
    assert(u->m_size == 1);
    glUniformMatrix3fv(u->m_location, 1, GL_FALSE, &m_data[0][0]);
}

template <>
void UniformValueT<glm::mat4>::bind(Uniform *u) {
    assert(u->m_size == 1);
    glUniformMatrix4fv(u->m_location, 1, GL_FALSE, &m_data[0][0]);
}

template <>
void UniformValueT<std::vector<glm::vec2>>::bind(Uniform *u) {
    assert(u->m_size <= m_data.size());
    glUniform2fv(u->m_location, u->m_size, (const float *)m_data.data());
}

template <>
void UniformValueT<std::vector<glm::vec3>>::bind(Uniform *u) {
    assert(u->m_size <= m_data.size());
    glUniform3fv(u->m_location, u->m_size, (const float *)m_data.data());
}

template <>
void UniformValueT<std::vector<glm::vec4>>::bind(Uniform *u) {
    assert(u->m_size <= m_data.size());
    glUniform4fv(u->m_location, u->m_size, (const float *)m_data.data());
}


SGL_END