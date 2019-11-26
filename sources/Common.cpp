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




void PrintGLError(int error) {
#define item(x) case x: cout << #x << endl; break
    switch (error){
        item(GL_NO_ERROR);
        item(GL_INVALID_ENUM);
        item(GL_INVALID_VALUE);
        item(GL_INVALID_OPERATION);
        item(GL_INVALID_FRAMEBUFFER_OPERATION);
        item(GL_OUT_OF_MEMORY);
        item(GL_STACK_UNDERFLOW);
        item(GL_STACK_OVERFLOW);
        default:
            cout <<"unknown error" << endl;
    }
#undef item
}




SGL_END