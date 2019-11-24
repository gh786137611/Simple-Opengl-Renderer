//
// Created by mm on 2019/11/19.
//

#ifndef SGLRENDER_VERTEXBUFFER_H
#define SGLRENDER_VERTEXBUFFER_H

#include "Common.h"

SGL_BEGIN

class VertexBuffer {
    friend ShaderMaterial;

public:
    ~VertexBuffer();
    static std::shared_ptr<VertexBuffer> create(const void *data, size_t size, size_t nPerVertex);
    unsigned get_element_number(){
        return m_size / m_nPerVertex;
    }
private:
    VertexBuffer(const void * data, size_t size, size_t nPerVertex);
    void bind(Attrib * a);
private:
    unsigned m_handle;
    unsigned m_size;
    size_t m_nPerVertex;
    char * m_pendingData;
};


SGL_END

#endif //SGLRENDER_VERTEXBUFFER_H
