//
// Created by mm on 2019/11/20.
//

#include "Texture.h"


SGL_BEGIN

std::shared_ptr<Texture2D> Texture::create_2D_texture() {
    return std::shared_ptr<Texture2D>(new Texture2D{});
}

std::shared_ptr<TextureCube> Texture::create_cube_texture() {
    return std::shared_ptr<TextureCube>(new TextureCube{});
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


void Texture2D::bind(unsigned unit) {
    if (0 == m_handle) {
        glGenTextures(1, &m_handle);
    }
    assert(m_handle);
    if (m_pendingData.level < 0) {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, m_handle);
    }else {
        glActiveTexture(GL_TEXTURE0 + unit);
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
    glUniform1i(GL_TEXTURE_2D, unit);
}

void TextureCube::bind(unsigned unit) {
    if (0 == m_handle) {
        glGenTextures(1, &m_handle);
    }
    assert(m_handle);
    if (m_pendingData.level < 0) {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_handle);
    }else {
        glActiveTexture(GL_TEXTURE0 + unit);
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
    glUniform1i(GL_TEXTURE_CUBE_MAP, unit);
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