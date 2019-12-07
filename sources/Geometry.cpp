//
// Created by mm on 2019/11/19.
//

#include "Geometry.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

SGL_BEGIN

Ptr<Geometry> Geometry::create() {
    return Ptr<Geometry>(new Geometry);
}


void Geometry::add_attribute(const std::string &name, Ptr<VertexBuffer> vbo) {
    m_attributes[name] = vbo;
}

Ptr<VertexBuffer> Geometry::get_attribute(const std::string &name) {
    auto it = m_attributes.find(name);
    if (it != m_attributes.end())
        return it->second;
    else
        return Ptr<VertexBuffer>{};
}

void Geometry::set_indices(Ptr<IndexBuffer> index) {
    m_indices = index;
}


Ptr<Geometry> Geometry::create_unit_box() {
    using glm::vec3;
    float f = 0.5;
    vec3 vertex []={
            vec3(f, -f, f), vec3(f, -f, -f), vec3(f, f, -f),
            vec3(f, -f, f), vec3(f, f, -f), vec3(f, f, f),
            vec3(-f, -f, f),  vec3(-f, f, -f), vec3(-f, -f, -f),
            vec3(-f, -f, f),  vec3(-f, f, f), vec3(-f, f, -f),

            vec3(-f, f, f),  vec3(f, f, f), vec3(f, f, -f),
            vec3(-f, f, f),  vec3(f, f, -f),  vec3(-f, f, -f),
            vec3(-f, -f, f),  vec3(f, -f, f), vec3(f, -f, -f),
            vec3(-f, -f, f),  vec3(f, -f, -f),  vec3(-f, -f, -f),

            vec3(-f, -f, f),  vec3(f, -f, f), vec3(f, f, f),
            vec3(-f, -f, f),  vec3(f, f, f), vec3(-f, f, f),
            vec3(-f, -f, -f),   vec3(f, f, -f),vec3(f, -f, -f),
            vec3(-f, -f, -f),  vec3(-f, f, -f),vec3(f, f, -f)
    };
//    float vertex[] = {
//            // positions
//            -1.0f,  1.0f, -1.0f,
//            -1.0f, -1.0f, -1.0f,
//            1.0f, -1.0f, -1.0f,
//            1.0f, -1.0f, -1.0f,
//            1.0f,  1.0f, -1.0f,
//            -1.0f,  1.0f, -1.0f,
//
//            -1.0f, -1.0f,  1.0f,
//            -1.0f, -1.0f, -1.0f,
//            -1.0f,  1.0f, -1.0f,
//            -1.0f,  1.0f, -1.0f,
//            -1.0f,  1.0f,  1.0f,
//            -1.0f, -1.0f,  1.0f,
//
//            1.0f, -1.0f, -1.0f,
//            1.0f, -1.0f,  1.0f,
//            1.0f,  1.0f,  1.0f,
//            1.0f,  1.0f,  1.0f,
//            1.0f,  1.0f, -1.0f,
//            1.0f, -1.0f, -1.0f,
//
//            -1.0f, -1.0f,  1.0f,
//            -1.0f,  1.0f,  1.0f,
//            1.0f,  1.0f,  1.0f,
//            1.0f,  1.0f,  1.0f,
//            1.0f, -1.0f,  1.0f,
//            -1.0f, -1.0f,  1.0f,
//
//            -1.0f,  1.0f, -1.0f,
//            1.0f,  1.0f, -1.0f,
//            1.0f,  1.0f,  1.0f,
//            1.0f,  1.0f,  1.0f,
//            -1.0f,  1.0f,  1.0f,
//            -1.0f,  1.0f, -1.0f,
//
//            -1.0f, -1.0f, -1.0f,
//            -1.0f, -1.0f,  1.0f,
//            1.0f, -1.0f, -1.0f,
//            1.0f, -1.0f, -1.0f,
//            -1.0f, -1.0f,  1.0f,
//            1.0f, -1.0f,  1.0f
//    };
    //for (auto & e:vertex)e *= 0.5f;
    vec3 normal[]={
            vec3(1,0,0), vec3(1,0,0),vec3(1,0,0),
            vec3(1,0,0), vec3(1,0,0),vec3(1,0,0),
            vec3(-1,0,0), vec3(-1,0,0),vec3(-1,0,0),
            vec3(-1,0,0), vec3(-1,0,0),vec3(-1,0,0),

            vec3(0,1,0), vec3(0,1,0),vec3(0,1,0),
            vec3(0,1,0), vec3(0,1,0),vec3(0,1,0),
            vec3(0,-1,0), vec3(0,-1,0),vec3(0,-1,0),
            vec3(0,-1,0), vec3(0,-1,0),vec3(0,-1,0),

            vec3(0,0,1),vec3(0,0,1),vec3(0,0,1),
            vec3(0,0,1),vec3(0,0,1),vec3(0,0,1),
            vec3(0,0,-1),vec3(0,0,-1),vec3(0,0,-1),
            vec3(0,0,-1),vec3(0,0,-1),vec3(0,0,-1)
    };

    Ptr<Geometry> g = create();
    Ptr<VertexBuffer> vbo = VertexBuffer::create(vertex, sizeof(vertex), sizeof(float)*3);
    Ptr<VertexBuffer> nbo = VertexBuffer::create(normal, sizeof(normal), sizeof(float)*3);
    g->add_attribute("position", vbo);
    g->add_attribute("normal", nbo);
    return g;
}



SGL_END