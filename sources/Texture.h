//
// Created by mm on 2019/11/20.
//

#ifndef SGLRENDER_TEXTURE_H
#define SGLRENDER_TEXTURE_H

#include "Common.h"

SGL_BEGIN

class Texture {
    friend ShaderMaterial;
protected:
public:
    void set_filter(TextureParameter minFilter, TextureParameter magFilter) {
        m_minFilter = minFilter;
        m_magFilter = magFilter;
        m_needsUpdateParameter = true;
    }
    void set_wrap(TextureParameter s, TextureParameter t, TextureParameter r = TextureParameter::Clamp) {
        m_sWrap = s;
        m_tWrap = t;
        m_rWrap = r;
        m_needsUpdateParameter = true;
    }
    virtual ~Texture(){}
    void generate_mipmap() {
        m_needsGenerateMipmap = true;
    }
    static Ptr<Texture2D> create_2D_texture();
    static Ptr<TextureCube> create_cube_texture();

protected:
    Texture(){
        m_handle = 0;
        m_minFilter = m_magFilter = TextureParameter::Linear;
        m_rWrap = m_tWrap = m_sWrap = TextureParameter::Clamp;
        m_needsUpdateParameter = true;
        m_needsGenerateMipmap = false;
    }
    unsigned handle() const{
        return m_handle;
    }
    virtual void bind(Uniform *u) = 0;
protected:
    unsigned m_handle;
    TextureParameter m_minFilter, m_magFilter;
    TextureParameter m_sWrap, m_tWrap, m_rWrap;
    bool m_needsUpdateParameter;
    bool m_needsGenerateMipmap;
};

class Texture2D: public Texture {
    friend Texture;
    struct DataTag {
        int level;
        int width, height;
        char * data;
        PixelFormat internal, external;
        TextureDataType type;
    };
public:
    ~Texture2D() override ;

    void set_data(PixelFormat internalFormat, int width, int height, PixelFormat format, TextureDataType type, const void *data) {
        m_pendingData.level = 0;
        m_pendingData.internal = internalFormat;
        m_pendingData.external = format;
        m_pendingData.width = width;
        m_pendingData.height = height;
        m_pendingData.type = type;
        if (m_pendingData.data) {
            delete[] m_pendingData.data;
            m_pendingData.data = nullptr;
        }
        if (data) {
            int len = width * height * ChannelOfPixelFormat(format) * SizeOfTextureDataType(type);
            m_pendingData.data = new char[len];
            memcpy(m_pendingData.data, data, len);
        }
    }

private:
    void update_parameter() {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, int(m_minFilter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, int(m_magFilter));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, int(m_sWrap));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, int(m_tWrap));
    }
private:
    void bind(Uniform *u) override;

    Texture2D(){
        m_pendingData.data = nullptr;
        m_pendingData.level = -1;
        m_handle = 0;
    }
private:
    DataTag m_pendingData;
};


class TextureCube: public Texture {
    friend Texture;
    struct DataTag {
        int level;
        int width, height;
        char *data;
        PixelFormat internal, external;
        TextureDataType type;
    };
public:
    ~TextureCube()override ;
    void set_data(PixelFormat internalFormat, int width, int height, PixelFormat format, TextureDataType type, const void * const*data) {
        m_pendingData.level = 0;
        m_pendingData.internal = internalFormat;
        m_pendingData.external = format;
        m_pendingData.width = width;
        m_pendingData.height = height;
        m_pendingData.type = type;
        if (m_pendingData.data) {
            delete[] m_pendingData.data;
            m_pendingData.data = nullptr;
        }
        if (data) {
            int len = width * height * ChannelOfPixelFormat(format) * SizeOfTextureDataType(type);
            m_pendingData.data = new char[len * 6];
            for (int i = 0;  i<6; ++i) {
                memcpy(m_pendingData.data + len *i, data[i], len);
            }
        }
    }
private:
    void bind(Uniform *u) override ;
    TextureCube() {
        m_pendingData.data = nullptr;
        m_pendingData.level = -1;
        m_handle = 0;
    }

    void update_parameter() {
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, int(m_minFilter));
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, int(m_magFilter));
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, int(m_sWrap));
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, int(m_tWrap));
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, int(m_rWrap));
    }
private:
    DataTag m_pendingData;
};

SGL_END
#endif //SGLRENDER_TEXTURE_H
