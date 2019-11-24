//
// Created by mm on 2019/11/19.
//

#include "VertexBuffer.h"
#include "Attrib.h"

SGL_BEGIN

VertexBuffer::VertexBuffer(const void *data, size_t size, size_t nPerVertex) {
    m_handle = 0;
    char * p  = new char[size];
    memcpy(p, data, size);
    m_pendingData = p;
    m_size = size;
    m_nPerVertex = nPerVertex;
}

void VertexBuffer::bind(Attrib * a)  {
    if (0 == m_handle) {
        glGenBuffers(1, &m_handle);
        assert(m_handle);
    }
    if (m_pendingData) {
        glBindBuffer(GL_ARRAY_BUFFER, m_handle);
        glBufferData(GL_ARRAY_BUFFER, m_size, m_pendingData, GL_DYNAMIC_DRAW);
        m_pendingData = nullptr;
    }else{
        glBindBuffer(GL_ARRAY_BUFFER, m_handle);
    }
    glVertexAttribPointer(a->m_location, a->m_size, a->m_type, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(a->m_location);
}

VertexBuffer::~VertexBuffer() {
    if (m_handle > 0) {
        glDeleteBuffers(1, &m_handle);
        m_handle = 0;
    }
    if (m_pendingData) {
        delete [] m_pendingData;
    }
}

std::shared_ptr<VertexBuffer> VertexBuffer::create(const void *data, size_t size, size_t nPerVertex) {
    return std::shared_ptr<VertexBuffer>(new VertexBuffer(data, size, nPerVertex));
}



SGL_END