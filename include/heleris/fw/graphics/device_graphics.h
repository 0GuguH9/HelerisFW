#ifndef HRS_GRAPHICS_DEVICE_H
#define HRS_GRAPHICS_DEVICE_H

#include "../window.h"

enum HRSPlatform {
    HRS_PLATFORM_LINUX,
    HRS_PLATFORM_WINDOWS,
};

typedef struct HRSDeviceGraphics {
    enum HRSPlatform platform;
} HRSDeviceGraphics;

HRSDeviceGraphics hrsdgr_create();

#endif