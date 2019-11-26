//
// Created by mm on 2019/11/19.
//

#ifndef SGLRENDER_GEOMETRY_H
#define SGLRENDER_GEOMETRY_H

#include "Common.h"

SGL_BEGIN


class Geometry {
    friend TriMesh;
public:
    static Ptr<Geometry> create();
    void add_attribute(const std::string & name, Ptr<VertexBuffer> vbo);
    void set_indices(Ptr<IndexBuffer> index);
    Ptr<VertexBuffer> get_attribute(const std::string & name);

public:
    static Ptr<Geometry> create_unit_box();
private:
    std::map<std::string, Ptr<VertexBuffer>> m_attributes;
    Ptr<IndexBuffer> m_indices;
};

SGL_END
#endif //SGLRENDER_GEOMETRY_H
