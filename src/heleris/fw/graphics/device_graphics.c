#include "heleris/fw/graphics/device_graphics.h"

#include <stdio.h>

HRSDeviceGraphics hrsdgr_create() {

    HRSDeviceGraphics _deviceGraphics;

    _deviceGraphics.platform = PLATFORM;
    _deviceGraphics.platformName = PLATFORM_NAME;

    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &_deviceGraphics.maxTextureSize);
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &_deviceGraphics.maxTextureUnits);
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &_deviceGraphics.maxVertexAttribs);
    glGetIntegerv(GL_MAX_SAMPLES, &_deviceGraphics.maxMSAA);
    glGetIntegerv(GL_MAX_DRAW_BUFFERS, &_deviceGraphics.maxDrawBuffers);

    return _deviceGraphics;
}

void hrsdgr_print(const HRSDeviceGraphics *_deviceGraphics) {
    
    printf("Platform: %s\n", _deviceGraphics->platformName);
    printf("Max Texture Size: %d\n", _deviceGraphics->maxTextureSize);
    printf("Max Texture Units: %d\n", _deviceGraphics->maxTextureUnits);
    printf("Max Vertex Attribs: %d\n", _deviceGraphics->maxVertexAttribs);
    printf("Max MSAA: %d\n", _deviceGraphics->maxMSAA);
    printf("Max Draw Buffers: %d\n", _deviceGraphics->maxDrawBuffers);
}
