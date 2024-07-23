#include "heleris/fw/graphics/device_graphics.h"

HRSDeviceGraphics hrsdgr_create() {

    HRSDeviceGraphics _deviceGraphics;

#ifdef __linux
    _deviceGraphics.platform = HRS_PLATFORM_LINUX;
#elif defined(__WIN32) || defined(__WIN64)
    deviceGraphics.platform = HRS_PLATFORM_WINDOWS;
#endif    

    return _deviceGraphics;
}
