//
// Created by mm on 2019/11/19.
//

#include "IndexBuffer.h"


SGL_BEGIN


IndexBuffer::IndexBuffer(const unsigned *indices, size_t size) {
    m_pendingData = new unsigned[size];
    memcpy(m_pendingData, indices, sizeof(unsigned) * size);
    m_size = size;
}

void IndexBuffer::bind() {
    if (0 == m_handle) {
        glGenBuffers(1, &m_handle);
        assert(m_handle);
    }
    if (m_pendingData) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * m_size, m_pendingData, GL_DYNAMIC_DRAW);
        delete[] m_pendingData;
        m_pendingData = nullptr;
    }else{
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
    }
}

IndexBuffer::~IndexBuffer() {
    if (m_handle) {
        glDeleteBuffers(1,&m_handle);
        m_handle = 0;
    }
    if (m_pendingData) {
        delete []m_pendingData;
        m_pendingData = nullptr;
    }
}

std::shared_ptr<IndexBuffer> IndexBuffer::create(const unsigned *indices, size_t size) {
    return std::shared_ptr<IndexBuffer>(new IndexBuffer(indices, size));
}





SGL_END