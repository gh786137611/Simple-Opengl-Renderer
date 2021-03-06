//
// Created by mm on 2019/11/19.
//

#ifndef SGLRENDER_TRIMESH_H
#define SGLRENDER_TRIMESH_H

#include "Common.h"
#include "Object3D.h"

SGL_BEGIN

class TriMesh: public Object3D {
public:
    static Ptr<TriMesh> create(Ptr<Geometry> & geometry, Ptr<ShaderMaterial>& material,
            const std::string &name="");
    Ptr<Geometry> & geometry() {
        return m_geometry;
    }
    Ptr<ShaderMaterial>& material() {
        return m_material;
    }
    void set_cull_face(Face face);
    void set_polygon_mode(Face face, PolygonMode mode);


protected:
    void draw(const Camera *camera, const glm::mat4 & parentModelMat = glm::mat4(1.0f)) override;
    void state_switch() override ;
    TriMesh(Ptr<Geometry> & geometry, Ptr<ShaderMaterial>& material);
protected:
    std::function<void(void)> m_cullFace;
    std::function<void(void)> m_polygonMode;
};

SGL_END
#endif //SGLRENDER_TRIMESH_H
