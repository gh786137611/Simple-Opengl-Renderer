//
// Created by mm on 2019/11/22.
//

#ifndef SGLRENDER_SCENE_H
#define SGLRENDER_SCENE_H

#include "Common.h"
SGL_BEGIN
class Scene {
public:
    void draw(const Camera * camera);
    static Ptr<Scene> create();
    void add(Ptr<Object3D> obj){
        if (obj)
            m_children.push_back(obj);
    }
    Ptr<Object3D> remove(const std::string & name);
    Ptr<Object3D> find(const std::string & name);
private:
    void draw_obj(Ptr<Object3D> & obj, const Camera * camera, const glm::mat4 & mat);
private:
    std::list<Ptr<Object3D>> m_children;
};

SGL_END
#endif //SGLRENDER_SCENE_H
