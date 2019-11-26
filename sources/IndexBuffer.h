//
// Created by mm on 2019/11/19.
//

#ifndef SGLRENDER_INDEXBUFFER_H
#define SGLRENDER_INDEXBUFFER_H

#include "Common.h"


SGL_BEGIN

class IndexBuffer {
    friend TriMesh;
public:
    static Ptr<IndexBuffer> create(const unsigned *indices, size_t size);
    ~IndexBuffer();
private:
    IndexBuffer(const unsigned * indices, size_t size);
    void bind();
private:
    unsigned m_handle;
    unsigned m_size;
    unsigned * m_pendingData;
};

SGL_END
#endif //SGLRENDER_INDEXBUFFER_H
