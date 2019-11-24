//
// Created by mm on 2019/11/21.
//

#include "Object3D.h"

SGL_BEGIN
void Object3D::update_modelMatrix(){
    m_modelMatrix = glm::mat4(1.0);
    m_modelMatrix[0][0] = m_scale[0];
    m_modelMatrix[1][1] = m_scale[1];
    m_modelMatrix[2][2] = m_scale[2];
    m_modelMatrix = m_rotation * m_modelMatrix;
    m_modelMatrix[3][0] = m_position[0];
    m_modelMatrix[3][1] = m_position[1];
    m_modelMatrix[3][2] = m_position[2];
}


std::shared_ptr<Object3D> Object3D::create() {
    return std::shared_ptr<Object3D>(new Object3D);
}

SGL_END