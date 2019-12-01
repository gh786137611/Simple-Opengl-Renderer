//
// Created by mm on 2019/11/22.
//

#include "Scene.h"
#include "Object3D.h"

SGL_BEGIN
Ptr<Scene> Scene::create(){
    return Ptr<Scene>(new Scene);
}

void Scene::draw(const SGL::Camera *camera) {
    glm::mat4 mat(1.0f);
    for (Ptr<Object3D>& ptr: m_children) {
        if (ptr->m_visible) {
            draw_obj(ptr, camera, mat);
        }
    }
}

void Scene::draw_obj(Ptr<Object3D> & obj, const Camera * camera, const glm::mat4 & mat) {
    obj->draw(camera, mat);
    glm::mat4 t = mat * obj->m_modelMatrix;
    for (Ptr<Object3D>& ptr: obj->m_children) {
        if (ptr->m_visible) {
            draw_obj(ptr, camera, t);
        }
    }
}

Ptr<Object3D> Scene::remove(const std::string &name) {
    auto it = m_children.begin();
    for (; it !=m_children.end(); ++it){
        if ((*it)->m_name == name) {
            break;
        }
    }
    if (it != m_children.end()){
        Ptr<Object3D> ptr = *it;
        m_children.erase(it);
        return ptr;
    }else{
        for (Ptr<Object3D> & child : m_children){
            auto t = child->remove_child(name);
            if (t) {
                return t;
            }
        }
    }

    return Ptr<Object3D>{};
}
SGL_END