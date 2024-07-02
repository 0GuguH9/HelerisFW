#include "headers/color.h"

HRSColor tnxclr_create(uint8_t r, uint8_t g, uint8_t b) {

    return tnxclr_create_op(r, g, b, 255);
}

HRSColor tnxclr_create_op(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {

    HRSColor color = {r, g, b, a};
    return color;
}
