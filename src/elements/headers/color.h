#ifndef HELERIS_ELEMENTS_COLOR_H
#define HELERIS_ELEMENTS_COLOR_H

#include <stdint.h>

typedef struct HRSColor {
    uint8_t r; // The red of color
    uint8_t g; // The green of color
    uint8_t b; // The blue of color
    uint8_t a; // The alpha of color. 0 is transparent and 255 is opaque
} HRSColor;

HRSColor hrsclr_create(uint8_t r, uint8_t g, uint8_t b);

HRSColor hrsclr_create_op(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

#endif