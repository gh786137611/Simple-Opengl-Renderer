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
    static std::shared_ptr<Geometry> create();
    void add_attribute(const std::string & name, std::shared_ptr<VertexBuffer> vbo);
    void set_indices(std::shared_ptr<IndexBuffer> index);
    std::shared_ptr<VertexBuffer> get_attribute(const std::string & name);

public:
    static std::shared_ptr<Geometry> create_unit_box();
private:
    std::map<std::string, std::shared_ptr<VertexBuffer>> m_attributes;
    std::shared_ptr<IndexBuffer> m_indices;
};

SGL_END
#endif //SGLRENDER_GEOMETRY_H
