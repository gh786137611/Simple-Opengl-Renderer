//
// Created by mm on 2019/11/19.
//

#include "Geometry.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

SGL_BEGIN

std::shared_ptr<Geometry> Geometry::create() {
    return std::shared_ptr<Geometry>(new Geometry);
}


void Geometry::add_attribute(const std::string &name, std::shared_ptr<VertexBuffer> vbo) {
    m_attributes[name] = vbo;
}

std::shared_ptr<VertexBuffer> Geometry::get_attribute(const std::string &name) {
    auto it = m_attributes.find(name);
    if (it != m_attributes.end())
        return it->second;
    else
        return std::shared_ptr<VertexBuffer>{};
}

void Geometry::set_indices(std::shared_ptr<IndexBuffer> index) {
    m_indices = index;
}


std::shared_ptr<Geometry> Geometry::create_unit_box() {
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

    std::shared_ptr<Geometry> g = create();
    std::shared_ptr<VertexBuffer> vbo = VertexBuffer::create(vertex, sizeof(vertex), sizeof(float)*3);
    std::shared_ptr<VertexBuffer> nbo = VertexBuffer::create(normal, sizeof(normal), sizeof(float)*3);
    g->add_attribute("position", vbo);
    return g;
}



SGL_END