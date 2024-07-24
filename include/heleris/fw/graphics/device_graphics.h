#ifndef HRS_GRAPHICS_DEVICE_H
#define HRS_GRAPHICS_DEVICE_H

#include "../types.h"

#ifdef __linux
    #define PLATFORM  HRS_PLATFORM_LINUX
    #define PLATFORM_NAME "Linux"
#elif defined(__WIN32)
    #define PLATFORM  HRS_PLATFORM_WINDOWS
    #define PLATFORM_NAME "Windows"
#elif
    #ifndef HRS_SUPPORT_UNKNOWN_PLATFORM
        #error "Unknow platform"
    #endif
    #define PLATFORM HRS_PLATFORM_UNKNOWN
    #define PLATFORM_NAME "Unknown"
#endif

#ifndef HELERIS_OPEN_GL_INCLUDE_ALREADY
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define HELERIS_OPEN_GL_INCLUDE_ALREADY
#endif

enum HRSPlatform {
    HRS_PLATFORM_LINUX,
    HRS_PLATFORM_WINDOWS,
    HRS_PLATOFORM_UNKNOWN,
};

/*
 * This represent device graphics information
 * Normally the data is the graphical limits of device
 * If you want to make your software more compatible, use the minimal consts
 */
typedef struct HRSDeviceGraphics {
    enum HRSPlatform platform;  // Platform
    string_t platformName;      // Platform Name
    int maxTextureSize;         // Max Texture Size
    int maxTextureUnits;        // Max Texture Units
    int maxVertexAttribs;       // Max Vertex Attributes
    int maxMSAA;                // Max Multi Sample Anti-Aliasing
    int maxDrawBuffers;         // Max Draw Buffers
} HRSDeviceGraphics;

/*
 * Create a device graphics (i.e., device graphical limits).
 */
HRSDeviceGraphics hrsdgr_create();

/*
 * Print all Device data
 */
void hrsdgr_print(const HRSDeviceGraphics *deviceGraphics);

#endif