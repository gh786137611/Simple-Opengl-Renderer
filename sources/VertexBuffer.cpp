//
// Created by mm on 2019/11/19.
//

#include "VertexBuffer.h"
#include "Attrib.h"


SGL_BEGIN


VertexBuffer::VertexBuffer(const void *data, size_t size, size_t nPerVertex) {
    m_handle = 0;
    m_pendingData = new DataCopyBuffer(data, size);
    m_size = size;
    m_nPerVertex = nPerVertex;
}

void VertexBuffer::set_data(const void *data, size_t size, size_t nPerVertex) {
    if (m_pendingData) {
        delete m_pendingData;
        m_pendingData = nullptr;
    }
    m_pendingData = new DataCopyBuffer(data, size);
    m_size = size;
    m_nPerVertex = nPerVertex;
}

void VertexBuffer::set_subdata(const void *data, size_t offset, size_t size) {
    DataBuffer *buffer = new SubDataCopyBuffer(data, offset, size);
    m_pendingSubData.push_back(buffer);
}

void VertexBuffer::bind(Attrib * a)  {
    if (0 == m_handle) {
        glGenBuffers(1, &m_handle);
        assert(m_handle);
    }
    if (m_pendingData) {
        m_pendingData->updateTo(GL_ARRAY_BUFFER, m_handle);
        delete m_pendingData;
        m_pendingData = nullptr;
    }

    if (not m_pendingSubData.empty()) {
        for (DataBuffer *b : m_pendingSubData) {
            b->updateTo(GL_ARRAY_BUFFER, m_handle);
            delete b;
        }
        m_pendingSubData.clear();
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
    glVertexAttribPointer(a->m_location, a->m_size, a->m_type, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(a->m_location);
}

VertexBuffer::~VertexBuffer() {
    if (m_handle > 0) {
        glDeleteBuffers(1, &m_handle);
        m_handle = 0;
    }
    if (m_pendingData) {
        delete m_pendingData;
    }
    for (auto * ptr : m_pendingSubData) {
        delete ptr;
    }
}

Ptr<VertexBuffer> VertexBuffer::create(const void *data, size_t size, size_t nPerVertex) {
    return Ptr<VertexBuffer>(new VertexBuffer(data, size, nPerVertex));
}



SGL_END