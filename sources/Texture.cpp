//
// Created by mm on 2019/11/20.
//

#include "Texture.h"
#include "Uniform.h"


SGL_BEGIN

Ptr<Texture2D> Texture2D::create() {
    return Ptr<Texture2D>(new Texture2D{});
}


Texture2D::~Texture2D() {
    if (m_handle) {
        glDeleteTextures(1, &m_handle);
        m_handle = 0;
    }
    if (m_pendingData.data) {
        delete[] m_pendingData.data;
        m_pendingData.data = nullptr;
        m_pendingData.level = -1;
    }
}


void Texture2D::bind(Uniform *u) {
    if (0 == m_handle) {
        glGenTextures(1, &m_handle);
    }
    assert(m_handle);
    if (m_pendingData.level < 0) {
        glActiveTexture(GL_TEXTURE0 + u->m_textureUnit);
        glBindTexture(GL_TEXTURE_2D, m_handle);
    }else {
        glActiveTexture(GL_TEXTURE0 + u->m_textureUnit);
        glBindTexture(GL_TEXTURE_2D, m_handle);
        glTexImage2D(GL_TEXTURE_2D, m_pendingData.level, int(m_pendingData.internal), m_pendingData.width, m_pendingData.height, 0,
                     int(m_pendingData.external), int(m_pendingData.type), m_pendingData.data);

        m_pendingData.level = -1;
        if (m_pendingData.data) {
            delete[]m_pendingData.data;
            m_pendingData.data = nullptr;
        }
    }
    if (m_needsUpdateParameter) {
        update_parameter();
        m_needsUpdateParameter = false;
    }
    if (m_needsGenerateMipmap) {
        glGenerateMipmap(GL_TEXTURE_2D);
        m_needsGenerateMipmap = false;
    }
    glUniform1i(u->m_location, u->m_textureUnit);
}

Ptr<TextureCube> TextureCube::create(){
    return Ptr<TextureCube>(new TextureCube{});
}

void TextureCube::bind(Uniform *u) {
    if (0 == m_handle) {
        glGenTextures(1, &m_handle);
    }
    assert(m_handle);
    if (m_pendingData.level < 0) {
        glActiveTexture(GL_TEXTURE0 + u->m_textureUnit);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_handle);
    }else {
        glActiveTexture(GL_TEXTURE0 + u->m_textureUnit);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_handle);
        int len = m_pendingData.width * m_pendingData.height * ChannelOfPixelFormat(m_pendingData.external) * SizeOfTextureDataType(m_pendingData.type);
        for (int i = 0; i<6; ++i) {
            char * offset = nullptr;
            if (m_pendingData.data) {
                offset =  m_pendingData.data + len * i;
            }
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, m_pendingData.level, int(m_pendingData.internal), m_pendingData.width, m_pendingData.height, 0,
                         int(m_pendingData.external), int(m_pendingData.type), offset);
        }
        m_pendingData.level = -1;
        if (m_pendingData.data) {
            delete[]m_pendingData.data;
            m_pendingData.data = nullptr;
        }

    }
    if (m_needsUpdateParameter) {
        update_parameter();
        m_needsUpdateParameter = false;
    }
    if (m_needsGenerateMipmap) {
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
        m_needsGenerateMipmap = false;
    }

    glUniform1i(u->m_location, u->m_textureUnit);
}


TextureCube::~TextureCube() {
    if (m_handle) {
        glDeleteTextures(1, &m_handle);
        m_handle = 0;
    }
    if (m_pendingData.data) {
        delete[] m_pendingData.data;
        m_pendingData.data = nullptr;
        m_pendingData.level = -1;
    }
}


SGL_END