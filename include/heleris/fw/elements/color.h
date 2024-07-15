#ifndef HELERIS_ELEMENTS_COLOR_H
#define HELERIS_ELEMENTS_COLOR_H

#include "../types.h"

enum EHRSColorValue {
    HRS_COLOR_RGBA_R,
    HRS_COLOR_RGBA_G,
    HRS_COLOR_RGBA_B,
    HRS_COLOR_RGBA_A,
};

// Represents a RGBA color
typedef struct HRSColor {
    byte_t r; // The red of color
    byte_t g; // The green of color
    byte_t b; // The blue of color
    byte_t a; // The alpha of color. 0 is transparent and 255 is opaque
} HRSColor;

/*
 * Create a RGBA color from a RGB color
 */
HRSColor hrsclr_fromRGB(byte_t r, byte_t g, byte_t b);

/*
 * Create a color
 */
HRSColor hrsclr_fromRGBA(byte_t r, byte_t g, byte_t b, byte_t a);

/*
 * Create a RGBA color from a RGB float
 */
HRSColor hrsclr_fromFRGB(float r, float g, float b);

/*
 * Create a RGBA color from a RGBA float
 */
HRSColor hrsclr_fromFRGBA(float r, float g, float b, float a);

/*
 * Convert a color value to a float value
 */
float hrsclr_toFloat(HRSColor color, enum EHRSColorValue colorValue);

/*
 * Create a RGBA colo from a hexa (experimental)
 */
HRSColor hrsclr_fromHexa(string_t hexa);

/*
 * Convert to a string
 */
string_t hrsclr_toString(HRSColor color);

#endif