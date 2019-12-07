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


Ptr<Object3D> Object3D::create() {
    return Ptr<Object3D>(new Object3D);
}

Ptr<Object3D> Object3D::remove_child(const std::string &name) {
    auto it = m_children.begin();
    for (; it != m_children.end(); ++it) {
        if ((*it)->m_name == name) {
            break;
        }
    }
    if (it != m_children.end()) {
        Ptr<Object3D> ptr = *it;
        m_children.erase(it);
        return ptr;
    }else{
        for (auto & child : m_children){
            auto t = child->remove_child(name);
            if (t) {
                return t;
            }
        }
    }
    return Ptr<Object3D>{};
}

Ptr<Object3D> Object3D::find(const std::string &name) {
    auto it = m_children.begin();
    for (; it != m_children.end(); ++it) {
        if ((*it)->m_name == name) {
            break;
        }
    }
    if (it != m_children.end()) {
        return *it;
    }else{
        for (auto & child : m_children){
            auto t = child->find(name);
            if (t) {
                return t;
            }
        }
    }
    return Ptr<Object3D>{};
}
SGL_END