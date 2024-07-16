#include "heleris/fw/elements/color.h"

#include "heleris/fw/errors/error_presets.h"

#include <string.h>

HRSColor hrsclr_fromRGB(byte_t r, byte_t g, byte_t b) {

    return hrsclr_fromRGBA(r, g, b, 255);
}

HRSColor hrsclr_fromRGBA(byte_t r, byte_t g, byte_t b, byte_t a) {

    HRSColor color = {r, g, b, a};
    return color;
}

HRSColor hrsclr_fromFRGB(float r, float g, float b) {

    return hrsclr_fromFRGBA(r, g, b, 1.0f);
}

HRSColor hrsclr_fromFRGBA(float r, float g, float b, float a) {

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

HRSColor hrsclr_fromHexa(string_t hexa) {

    int size = strlen(hexa);

    if (size < 6 || size > 9) {

        errpre_invalidArgument("string_t hexa (from hrsclr_fromHexa)");

        return hrsclr_fromRGB(0, 0, 0);
    }

    string_t formatedHexa = hexa;

    bool hasHashtag = hexa[0] == '#' ? true : false;

    for (int i = hasHashtag ? 1 : 0 ; i < size; i ++)
        formatedHexa[i] = hexa[i];


    byte_t value[8] = {0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF, 0xF};
    
    for (int i = 0; i < hasHashtag ? size - 1: size; i++) {
        if (formatedHexa[i] >= '0' && formatedHexa[i] <= '9')
            value[i] = formatedHexa[i] - '0';
        else if (formatedHexa[i] >= 'a' && formatedHexa[i] <= 'f')
            value[i] = formatedHexa[i] - 'a' + 10;
        else if (formatedHexa[i] >= 'A' && formatedHexa[i] <= 'F')
            value[i] = formatedHexa[i] - 'A' + 10;
        else 
            errpre_invalidArgument("string_t hexa (from hrsclr_fromHexa, wrong hexa)");
    }
    
    HRSColor color = {0, 0, 0, 0};

    color.r = value[0];
    color.r <<= 4;
    color.r |= value[1];

    color.g = value[2];
    color.g <<= 4;
    color.g |= value[3];

    color.b = value[4];
    color.b <<= 4;
    color.b |= value[5];

    color.a = value[6];
    color.a <<= 4;
    color.a |= value[7];

    return color;
}

string_t hrsclr_toString(HRSColor color) {

    char buffer[50];
    snprintf(buffer, sizeof(buffer), "{R: %d, G: %d, B: %d, A: %d}\n", color.r, color.g, color.b, color.a);

    return strdup(buffer);
}
