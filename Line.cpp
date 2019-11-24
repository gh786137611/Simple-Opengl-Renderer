//
// Created by mm on 19-11-24.
//

#include "Line.h"
#include "ShaderMaterial.h"
#include "Geometry.h"
#include "Camera.h"
#include "Attrib.h"
#include "VertexBuffer.h"

SGL_BEGIN

Line::Line(std::shared_ptr<SGL::Geometry> geometry, std::shared_ptr<SGL::ShaderMaterial> material) {
    m_geometry = geometry;
    m_material = material;
    set_line_width(10.0f);
}

std::shared_ptr<Line> Line::create(std::shared_ptr<Geometry> geometry, std::shared_ptr<ShaderMaterial> material) {
    return std::shared_ptr<Line>{new Line{geometry, material}};
}

void Line::draw(const SGL::Camera *camera, const glm::mat4 &parentModelMat) {
    glm::mat4 modelview = camera->viewMatrix() * parentModelMat * m_modelMatrix;
    m_material->set_value("modelviewMatrix", modelview);
    m_material->set_value("projectionMatrix", camera->projectionMatrix());
    m_material->bind(m_geometry);
    state_switch();
    unsigned count = m_geometry->get_attribute("position")->get_element_number();
    glDrawArrays(GL_LINE_STRIP, 0, count);
}

void Line::set_line_width(float width) {
    m_lineWidth = [=](){
        glLineWidth(width);
    };
}

void Line::state_switch() {
    m_lineWidth();
}
SGL_END