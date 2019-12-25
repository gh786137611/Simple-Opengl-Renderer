//
// Created by mm on 19-11-24.
//

#ifndef SGLRENDER_LINE_H
#define SGLRENDER_LINE_H

#include "Common.h"
#include "Object3D.h"
SGL_BEGIN
class Line: public Object3D {
public:
    void set_line_width(float width);
    static Ptr<Line> create(Ptr<Geometry> geometry, Ptr<ShaderMaterial> material, const std::string & name = "");
    static Ptr<Line> create(const std::vector<glm::vec3> & vertex, const glm::vec3 & color, const std::string & name);
protected:
    Line(Ptr<Geometry> geometry, Ptr<ShaderMaterial> material);
    void draw(const Camera *camera, const glm::mat4 & parentModelMat = glm::mat4(1.0));
    void state_switch()override ;
protected:
    std::function<void(void)> m_lineWidth;
};

SGL_END
#endif //SGLRENDER_LINE_H
