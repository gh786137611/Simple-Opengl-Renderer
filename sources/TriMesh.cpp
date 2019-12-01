//
// Created by mm on 2019/11/19.
//

#include "TriMesh.h"
#include "Geometry.h"
#include "ShaderMaterial.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Camera.h"

SGL_BEGIN

TriMesh::TriMesh(Ptr<Geometry> &geometry, Ptr<ShaderMaterial> &material) {
    m_geometry = geometry;
    m_material = material;
    m_cullFace = [](){
        glDisable(GL_CULL_FACE);
    };
    m_polygonMode = [](){
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    };
}

void TriMesh::draw(const Camera *camera, const glm::mat4 & parentModelMat) {
    glm::mat4 modelview = camera->viewMatrix() * parentModelMat * m_modelMatrix;
    m_material->set_value("modelviewMatrix", modelview);
    m_material->set_value("projectionMatrix", camera->projectionMatrix());
    m_material->bind(m_geometry);
    state_switch();
    if (m_geometry->m_indices) {
        m_geometry->m_indices->bind();
        glDrawElements(GL_TRIANGLES, m_geometry->m_indices->m_size, GL_UNSIGNED_INT, nullptr);
    }else{
        unsigned count = m_geometry->get_attribute("position")->get_element_number();
        glDrawArrays(GL_TRIANGLES, 0, count);
    }
}

Ptr<TriMesh> TriMesh::create(Ptr<Geometry> &geometry,
                                         Ptr<ShaderMaterial> &material,
                                         const std::string & name) {
    auto ptr=  Ptr<TriMesh>(new TriMesh(geometry, material));
    ptr->m_name = name;
    return ptr;
}

void TriMesh::state_switch() {
    m_cullFace();
    m_polygonMode();
}

void TriMesh::set_cull_face(Face face){
    if (face == Face::None) {
        m_cullFace = [](){
            glDisable(GL_CULL_FACE);
        };
    }else{
        m_cullFace = [=](){
            glEnable(GL_CULL_FACE);
            glCullFace(int(face));
        };
    }
}
void TriMesh::set_polygon_mode(Face face, PolygonMode mode) {
    if (face != Face::None) {
        m_polygonMode = [=](){
            glPolygonMode(int(face), int(mode));
        };
    }
}
SGL_END