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

Line::Line(Ptr<SGL::Geometry> geometry, Ptr<SGL::ShaderMaterial> material) {
    m_geometry = geometry;
    m_material = material;
    set_line_width(1.0f);
}

Ptr<Line> Line::create(Ptr<Geometry> geometry, Ptr<ShaderMaterial> material,
        const std::string & name) {
    auto ptr =  Ptr<Line>{new Line{geometry, material}};
    ptr->m_name = name;
    return ptr;
}

void Line::draw(const SGL::Camera *camera, const glm::mat4 &parentModelMat) {
    glm::mat4 modelview = camera->viewMatrix() * parentModelMat * m_modelMatrix;
    if (m_material && m_geometry) {
        m_material->set_value("modelviewMatrix", modelview);
        m_material->set_value("projectionMatrix", camera->projectionMatrix());
        m_material->bind(m_geometry);
        state_switch();
        unsigned count = m_geometry->get_attribute("position")->get_element_number();
        glDrawArrays(GL_LINE_STRIP, 0, count);
    }
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