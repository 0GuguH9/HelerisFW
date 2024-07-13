#ifndef HRS_GRAPHICS_DEVICE_H
#define HRS_GRAPHICS_DEVICE_H

enum HRSDevice {
    HRS_DEVICE_LINUX,
    HRS_DEVICE_WINDOWS,
};

typedef struct HRSDeviceGraphics {
    enum HRSDevice device;
} HRSDeviceGraphics;

#endif