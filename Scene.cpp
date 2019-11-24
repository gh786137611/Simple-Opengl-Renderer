//
// Created by mm on 2019/11/22.
//

#include "Scene.h"
#include "Object3D.h"

SGL_BEGIN
std::shared_ptr<Scene> Scene::create(){
    return std::shared_ptr<Scene>(new Scene);
}

void Scene::draw(const SGL::Camera *camera) {
    glm::mat4 mat(1.0f);
    for (std::shared_ptr<Object3D>& ptr: m_children) {
        if (ptr->m_visible) {
            draw_obj(ptr, camera, mat);
        }
    }
}

void Scene::draw_obj(std::shared_ptr<Object3D> & obj, const Camera * camera, const glm::mat4 & mat) {
    obj->draw(camera, mat);
    glm::mat4 t = mat * obj->m_modelMatrix;
    for (std::shared_ptr<Object3D>& ptr: obj->m_children) {
        if (ptr->m_visible) {
            draw_obj(ptr, camera, t);
        }
    }
}

SGL_END