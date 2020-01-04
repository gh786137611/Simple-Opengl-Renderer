//
// Created by mm on 20-1-4.
//

#ifndef SGL_DATABUFFER_H
#define SGL_DATABUFFER_H

#include "Common.h"

SGL_BEGIN

class DataBuffer {
public:
    virtual void updateTo(unsigned target, unsigned buffer) = 0;
    virtual ~DataBuffer(){}
};

class DataCopyBuffer : public  DataBuffer{
public:
    DataCopyBuffer(const void *data, size_t n) {
        m_size = n;
        m_data = nullptr;
        if (data) {
            char * p  = new char[m_size];
            memcpy(p, data, m_size);
            m_data = p;
        }
    }

    void updateTo(unsigned target, unsigned buffer) override {
        glBindBuffer(target, buffer);
        glBufferData(target, m_size, m_data, GL_DYNAMIC_DRAW);
    }
    ~DataCopyBuffer(){
        if (m_data) {
            delete [] m_data;
        }
        m_data = nullptr;
        m_size = 0;
    }

private:
    const char *m_data;
    size_t m_size;
};


class SubDataCopyBuffer : public  DataBuffer{
public:
    SubDataCopyBuffer(const void *data, size_t offset, size_t size) {
        m_size = size;
        m_offset = offset;
        m_data = nullptr;
        if (data) {
            char * p  = new char[m_size];
            memcpy(p, data, m_size);
            m_data = p;
        }
    }

    void updateTo(unsigned target, unsigned buffer) override {
        glBindBuffer(target, buffer);
        glBufferSubData(target, m_offset, m_size, m_data);
        glBufferData(target, m_size, m_data, GL_DYNAMIC_DRAW);
    }
    ~SubDataCopyBuffer() {
        if (m_data) {
            delete [] m_data;
        }
        m_data = nullptr;
        m_size = 0;
    }
private:
    const char *m_data;
    size_t m_size;
    size_t m_offset;
};


class Tex2DDataCopyBuffer: public DataBuffer {
public:
    Tex2DDataCopyBuffer(PixelFormat internalFormat, int width, int height, PixelFormat format, TextureDataType type, const void *data) {
        m_internal = internalFormat;
        m_width = width;
        m_height = height;
        m_external = format;
        m_type = type;
        m_level = 0;
        m_data = nullptr;
        if (data) {
            int len = width * height * ChannelOfPixelFormat(format) * SizeOfTextureDataType(type);
            m_data = new char[len];
            memcpy(m_data, data, len);
        }
    }
    void updateTo(unsigned target, unsigned buffer) override  {
        glBindTexture(target, buffer);
        glTexImage2D(target, m_level, int(m_internal), m_width, m_height, 0,
                     int(m_external), int(m_type), m_data);
    }

    ~Tex2DDataCopyBuffer() {
        if (m_data) {
            delete []m_data;
        }
        m_data = nullptr;
        m_width = m_height = 0;
    }
private:
    int m_level;
    int m_width, m_height;
    char * m_data;
    PixelFormat m_internal, m_external;
    TextureDataType m_type;
};

class Tex2DSubDataCopyBuffer: public DataBuffer {
public:
    Tex2DSubDataCopyBuffer(int xoffset, int yoffset,
            int width, int height, PixelFormat format, TextureDataType type, const void *data) {
        m_width = width;
        m_height = height;
        m_external = format;
        m_type = type;
        m_level = 0;
        m_xoffset = xoffset;
        m_yoffset = yoffset;
        m_data = nullptr;
        if (data) {
            int len = width * height * ChannelOfPixelFormat(format) * SizeOfTextureDataType(type);
            m_data = new char[len];
            memcpy(m_data, data, len);
        }
    }

    void updateTo(unsigned target, unsigned buffer) override  {
        glBindTexture(target, buffer);
        glTexSubImage2D(target, m_level, m_xoffset, m_yoffset, m_width, m_height, int(m_external), m_type, m_data);
    }
    ~Tex2DSubDataCopyBuffer() {
        if (m_data) {
            delete[] m_data;
        }
        m_data = nullptr;
        m_width = m_height = 0;
    }
private:
    int m_level;
    int m_width, m_height;
    int m_xoffset, m_yoffset;
    char * m_data;
    PixelFormat m_external;
    TextureDataType m_type;
};

SGL_END
#endif //SGL_DATABUFFER_H
