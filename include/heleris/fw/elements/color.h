#ifndef HELERIS_ELEMENTS_COLOR_H
#define HELERIS_ELEMENTS_COLOR_H

#include "../types.h"

enum EHRSColorValue {
    HRS_COLOR_RGBA_R,
    HRS_COLOR_RGBA_G,
    HRS_COLOR_RGBA_B,
    HRS_COLOR_RGBA_A,
};

typedef struct HRSColor {
    byte_t r; // The red of color
    byte_t g; // The green of color
    byte_t b; // The blue of color
    byte_t a; // The alpha of color. 0 is transparent and 255 is opaque
} HRSColor;

HRSColor hrsclr_fromRGB(byte_t r, byte_t g, byte_t b);

HRSColor hrsclr_fromRGBA(byte_t r, byte_t g, byte_t b, byte_t a);

HRSColor hrsclr_fromFRGB(float r, float g, float b);

HRSColor hrsclr_fromFRGBA(float r, float g, float b, float a);

float hrsclr_toFloat(HRSColor color, enum EHRSColorValue colorValue);

HRSColor hrsclr_fromHexa(string_t hexa);

string_t hrsclr_toString(HRSColor color);

#endif