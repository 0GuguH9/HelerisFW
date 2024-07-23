#include "heleris/fw/elements/color.h"

#include "heleris/fw/errors/error_presets.h"

#include <string.h>

HRSColor hrsclr_fromRGB(const byte_t r, const byte_t g, const byte_t b) {

    return hrsclr_fromRGBA(r, g, b, 255);
}

HRSColor hrsclr_fromRGBA(const byte_t r, const byte_t g, const byte_t b, const byte_t a) {

    HRSColor _color = {r, g, b, a};
    return _color;
}

HRSColor hrsclr_fromFRGB(const float r, const float g, const float b) {

    return hrsclr_fromFRGBA(r, g, b, 1.0f);
}

HRSColor hrsclr_fromFRGBA(const float r, const float g, const float b, const float a) {

    HRSColor _color = {(byte_t)(BYTE_T_MAX * r), 
        (byte_t)(BYTE_T_MAX * g), 
        (byte_t)(BYTE_T_MAX * b), 
        (byte_t)(BYTE_T_MAX * a)};

    return _color;
}

float hrsclr_toFloat(const HRSColor _color, const enum EHRSColorValue colorValue) {

    switch (colorValue) {
        case HRS_COLOR_RGBA_R:
            return (float)_color.r / BYTE_T_MAX;
        break;
        case HRS_COLOR_RGBA_G:
            return (float)_color.g / BYTE_T_MAX;
        break;
        case HRS_COLOR_RGBA_B:
            return (float)_color.b / BYTE_T_MAX;
        break;
        case HRS_COLOR_RGBA_A:
            return (float)_color.a / BYTE_T_MAX;
        break;
    }

    errpre_invalidArgument("enum HRSColorValue colorValue");

    return 0;
}

HRSColor hrsclr_fromHexa(const string_t hexa) {

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
    
    HRSColor _color = {0, 0, 0, 0};

    _color.r = value[0];
    _color.r <<= 4;
    _color.r |= value[1];

    _color.g = value[2];
    _color.g <<= 4;
    _color.g |= value[3];

    _color.b = value[4];
    _color.b <<= 4;
    _color.b |= value[5];

    _color.a = value[6];
    _color.a <<= 4;
    _color.a |= value[7];

    return _color;
}

string_t hrsclr_toString(const HRSColor _color) {

    char buffer[50];
    snprintf(buffer, sizeof(buffer), "{R: %d, G: %d, B: %d, A: %d}\n", _color.r, _color.g, _color.b, _color.a);

    return strdup(buffer);
}
