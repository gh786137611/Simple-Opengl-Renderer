//
// Created by mm on 2019/11/25.
//

#include "Point.h"
#include "ShaderMaterial.h"
#include "Geometry.h"
#include "Camera.h"
#include "Attrib.h"
#include "VertexBuffer.h"

SGL_BEGIN

void Point::draw(const SGL::Camera *camera, const glm::mat4 &parentModelMat) {
    glm::mat4 modelview = camera->viewMatrix() * parentModelMat * m_modelMatrix;
    if (m_material && m_geometry) {
        m_material->set_value("modelviewMatrix", modelview);
        m_material->set_value("projectionMatrix", camera->projectionMatrix());
        m_material->bind(m_geometry);
        state_switch();
        unsigned count = m_geometry->get_attribute("position")->get_element_number();
        glDrawArrays(GL_POINTS, 0, count);
    }
}

Ptr<Point> Point::create(Ptr<SGL::Geometry> geometry, Ptr<SGL::ShaderMaterial> material,
        const std::string & name) {
    auto ptr =  Ptr<Point>(new Point(geometry, material));
    ptr->m_name = name;
    return ptr;
}

Ptr<Point> Point::create(const std::vector<glm::vec3> &vertex, const glm::vec3 &color, const std::string &name) {
    Ptr<VertexBuffer> vbo = VertexBuffer::create(vertex.data(), sizeof(glm::vec3) * vertex.size(), sizeof(glm::vec3));
    auto g = Geometry::create();
    g->add_attribute("position", vbo);
    auto m = ShaderMaterial::create(color_shader);
    m->set_value("color", color);
    auto ptr =  Ptr<Point>(new Point(g, m));
    ptr->m_name = name;
    return ptr;
}

void Point::set_size(float r) {
    m_pointSize = [=](){
        glPointSize(r);
    };
}

void Point::state_switch() {
    m_pointSize();
    m_smoothPoint();
}

void Point::set_smooth(bool smooth) {
    if (smooth) {
        m_smoothPoint = [](){
            glEnable(GL_POINT_SMOOTH);
        };
    }else{
        glDisable(GL_POINT_SMOOTH);
    };
}
SGL_END