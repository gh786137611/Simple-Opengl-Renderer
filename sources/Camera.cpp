//
// Created by mm on 2019/11/20.
//

#include "Camera.h"


SGL_BEGIN

Ptr<PerspectiveCamera> Camera::createPerspective() {
    auto camera = Ptr<PerspectiveCamera>(new PerspectiveCamera{});
    camera->lookat(glm::vec3(0.0, 0.0, 0.0),
                glm::vec3(0.0, 0.0, -1.0),
                glm::vec3(0.0, 1.0, 0.0));
    camera->perspective(0.002, 1.0, 0.1, 1000.0);
    return camera;
}

Ptr<OrthoCamera> Camera::createOrtho() {
    auto camera = Ptr<OrthoCamera>(new OrthoCamera);
    camera->lookat(glm::vec3(0.0, 0.0, 0.0),
                   glm::vec3(0.0, 0.0, -1.0),
                   glm::vec3(0.0, 1.0, 0.0));
    camera->ortho(-1,1,-1,1,1.f, 100.f);
    return camera;
}













SGL_END