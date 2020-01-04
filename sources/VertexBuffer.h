//
// Created by mm on 2019/11/19.
//

#ifndef SGLRENDER_VERTEXBUFFER_H
#define SGLRENDER_VERTEXBUFFER_H

#include "Common.h"
#include "DataBuffer.h"

SGL_BEGIN

class VertexBuffer {
    friend ShaderMaterial;

public:
    ~VertexBuffer();
    static Ptr<VertexBuffer> create(const void *data, size_t size, size_t nPerVertex);
    unsigned get_element_number(){
        return m_size / m_nPerVertex;
    }

    void set_data(const void * data, size_t size, size_t nPerVertex);
    void set_subdata(const void *data, size_t offset, size_t size);
private:
    VertexBuffer(const void * data, size_t size, size_t nPerVertex);
    void bind(Attrib * a);
private:
    unsigned m_handle;
    unsigned m_size;
    size_t m_nPerVertex;
    DataBuffer * m_pendingData;
    std::list<DataBuffer*> m_pendingSubData;
};


SGL_END

#endif //SGLRENDER_VERTEXBUFFER_H
