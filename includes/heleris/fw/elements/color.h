#ifndef HELERIS_ELEMENTS_COLOR_H
#define HELERIS_ELEMENTS_COLOR_H

#include "../types.h"

enum HRSColorValue {
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

HRSColor hrsclr_fromFloat(float r, float g, float b, float a);

float hrsclr_toFloat(HRSColor color, enum HRSColorValue colorValue);

/*
 * Not implemented
 */
HRSColor hrsclr_fromHexa(string_t hexa);

string_t hrsclr_toString(HRSColor color);

#endif