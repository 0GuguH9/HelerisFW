#ifndef HRS_GRAPHICS_DEVICE_H
#define HRS_GRAPHICS_DEVICE_H

#include "../elements/size.h"

enum HRSPlatform {
    HRS_PLATFORM_LINUX,
    HRS_PLATFORM_WINDOWS,
};

typedef struct HRSDeviceGraphics {
    enum HRSPlatform platform;
    HRSSize viewSize;
} HRSDeviceGraphics;

HRSDeviceGraphics hrsdgr_create();

#endif