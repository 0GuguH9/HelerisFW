#ifndef HELERIS_ELEMENTS_COLOR_H
#define HELERIS_ELEMENTS_COLOR_H

#include "../types.h"

#ifndef HELERIS_OPEN_GL_INCLUDE_ALREADY
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define HELERIS_OPEN_GL_INCLUDE_ALREADY
#endif

enum HRSColorTypes {
    HRS_COLOR_RGB = GL_RGB,
    HRS_COLOR_RGBA = GL_RGBA,
};

enum EHRSColorValue {
    HRS_COLOR_RGBA_R,
    HRS_COLOR_RGBA_G,
    HRS_COLOR_RGBA_B,
    HRS_COLOR_RGBA_A,
};

// Represents a RGBA _color
typedef struct HRSColor {
    byte_t r; // The red of color
    byte_t g; // The green of color
    byte_t b; // The blue of color
    byte_t a; // The alpha of color. 0 is transparent and 255 is opaque
} HRSColor;

/*
 * Create a RGBA color from a RGB color
 */
HRSColor hrsclr_fromRGB(const byte_t r, const byte_t g, const byte_t b);

/*
 * Create a color
 */
HRSColor hrsclr_fromRGBA(const byte_t r, const byte_t g, const byte_t b, const byte_t a);

/*
 * Create a RGBA color from a RGB float
 */
HRSColor hrsclr_fromFRGB(const float r, const float g, const float b);

/*
 * Create a RGBA color from a RGBA float
 */
HRSColor hrsclr_fromFRGBA(const float r, const float g, const float b, const float a);

/*
 * Convert a color value to a float value
 */
float hrsclr_toFloat(const HRSColor _color, const enum EHRSColorValue colorValue);

/*
 * Create a RGBA colo from a hexa (experimental)
 */
HRSColor hrsclr_fromHexa(const string_t hexa);

/*
 * Convert to a string
 */
string_t hrsclr_toString(const HRSColor color);

#endif