//
// Created by mm on 2019/11/21.
//

#ifndef SGLRENDER_OBJECT3D_H
#define SGLRENDER_OBJECT3D_H

#include "Common.h"

SGL_BEGIN
class Object3D {
    friend class Scene;
public:
    void set_scale(float x, float y, float z) {
        m_scale[0] = x;
        m_scale[1] = y;
        m_scale[2] = z;
        update_modelMatrix();
    }
    const glm::vec3 &get_scale()const{return m_scale;}
    void set_name(const std::string & name) {
        m_name = name;
    }
    const std::string & get_name()const{
        return m_name;
    }
    void set_position(const glm::vec3 & pos){
        m_position = pos;
        update_modelMatrix();
    }
    const glm::vec3 &get_position()const {
        return m_position;
    }
    void set_rotation(const glm::mat4 & rotation) {
        m_rotation = rotation;
        update_modelMatrix();
    }
    const glm::mat4 & get_rotation()const{
        return m_rotation;
    }

    const glm::mat4 & get_modelMatrix()const {
        return m_modelMatrix;
    }

    void add_child(Ptr<Object3D> & child) {
        if(child)
            m_children.push_back(child);
    }
    void set_visible(bool visible) {
        m_visible = visible;
    }

    Ptr<ShaderMaterial> & material() {
        return m_material;
    }

    Ptr<Geometry> & geometry() {
        return m_geometry;
    }

    bool get_visible()const{return m_visible;}
    Ptr<Object3D> find(const std::string & name);
    Ptr<Object3D> remove_child(const std::string & name);
    static Ptr<Object3D> create();
    ~Object3D(){}
protected:
    void update_modelMatrix();
    virtual void draw(const Camera *camera, const glm::mat4 & parentModelMat = glm::mat4(1.0)){}
    Object3D(){
        m_rotation = glm::mat4(1.0);
        m_scale = glm::vec3(1.0,1.0,1.0);
        m_position = glm::vec3(0,0, 0);
        update_modelMatrix();
        m_visible = true;
    }
    virtual void state_switch(){}
protected:
    glm::mat4 m_parentModelMatrix;
    glm::mat4 m_modelMatrix;
    glm::vec3 m_scale;
    glm::mat4 m_rotation;
    glm::vec3 m_position;
    Ptr<Geometry> m_geometry;
    Ptr<ShaderMaterial> m_material;
    std::list<Ptr<Object3D>> m_children;
    std::string m_name;
    bool m_visible;
};

SGL_END
#endif //SGLRENDER_OBJECT3D_H
