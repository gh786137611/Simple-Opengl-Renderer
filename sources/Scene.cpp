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

SGL_END