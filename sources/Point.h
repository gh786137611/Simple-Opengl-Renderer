//
// Created by mm on 2019/11/25.
//

#ifndef SGLRENDER_POINT_H
#define SGLRENDER_POINT_H

#include "Common.h"
#include "Object3D.h"

SGL_BEGIN

class Point : public Object3D {
public:
    static Ptr<Point> create(Ptr<SGL::Geometry> geometry, Ptr<SGL::ShaderMaterial> material,
            const std::string & name="");
    static Ptr<Point> create(const std::vector<glm::vec3> & vertex, const glm::vec3 & color, const std::string & name="");
    void set_size(float r);
    void set_smooth(bool smooth);
protected:
    Point(Ptr<SGL::Geometry> & geometry, Ptr<SGL::ShaderMaterial>& material) {
        m_material = material;
        m_geometry = geometry;
        set_size(1.f);
        set_smooth(true);
    }
    void state_switch() override ;
    void draw(const Camera *camera, const glm::mat4 & parentModelMat = glm::mat4(1.0)) override ;
protected:
    std::function<void(void)> m_pointSize;
    std::function<void(void)> m_smoothPoint;
};

SGL_END
#endif //SGLRENDER_POINT_H
