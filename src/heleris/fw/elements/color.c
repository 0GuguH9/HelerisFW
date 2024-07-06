#include "heleris/fw/elements/color.h"

#include "heleris/fw/errors/error_presets.h"

#include <string.h>

HRSColor hrsclr_fromFloat(float r, float g, float b, float a) {

    HRSColor color = {(byte_t)(BYTE_T_MAX * r), 
        (byte_t)(BYTE_T_MAX * g), 
        (byte_t)(BYTE_T_MAX * b), 
        (byte_t)(BYTE_T_MAX * a)};

    return color;
}

float hrsclr_toFloat(HRSColor color, enum EHRSColorValue colorValue) {

    switch (colorValue) {
        case HRS_COLOR_RGBA_R:
            return (float)color.r / BYTE_T_MAX;
        break;
        case HRS_COLOR_RGBA_G:
            return (float)color.g / BYTE_T_MAX;
        break;
        case HRS_COLOR_RGBA_B:
            return (float)color.b / BYTE_T_MAX;
        break;
        case HRS_COLOR_RGBA_A:
            return (float)color.a / BYTE_T_MAX;
        break;
    }

    errpre_invalidArgument("enum HRSColorValue colorValue");

    return 0;
}

string_t hrsclr_toString(HRSColor color) {

    char buffer[50];
    snprintf(buffer, sizeof(buffer), "{R: %d, G: %d, B: %d, A: %d}\n", color.r, color.g, color.b, color.a);

    return strdup(buffer);
}
