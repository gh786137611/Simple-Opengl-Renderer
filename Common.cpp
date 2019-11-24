//
// Created by mm on 2019/11/21.
//

#include "Common.h"

SGL_BEGIN

int ChannelOfPixelFormat(PixelFormat format) {
    switch (format) {
        case PixelFormat::RGB: return 3;
        case PixelFormat::RGBA: return 4;
        case PixelFormat::Red: return 1;
    }

    return 0;
}


int SizeOfTextureDataType(TextureDataType type) {
    switch (type) {
        case TextureDataType::UBYTE:return 1;
        case TextureDataType::BYTE:return 1;
        case TextureDataType::Float:return sizeof(float);
    }
    return 0;
}









SGL_END