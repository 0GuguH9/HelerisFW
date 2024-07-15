#ifndef HELERIS_ELEMENTS_SIZE_2_H
#define HELERIS_ELEMENTS_SIZE_2_H

#include "../types.h"

// Represents a size with width and a height
typedef struct HRSSize {
    int width;
    int height;
} HRSSize;

/*
 * Create a size
 */
HRSSize hrssz_create(int width, int height);

/*
 * Compare two sizes and return if are equals
 */
bool_t hrssz_equals(HRSSize size1, HRSSize size2);

/*
 * Return the area of a size
 */
int hrssz_area(HRSSize size); 

/*
 * Scale a size (aka uniform multiplication)
 */
HRSSize hrssz_scale(HRSSize size, float scale);

/*
 * Convert to a string
 */
string_t hrssz_toString(HRSSize size);

#endif