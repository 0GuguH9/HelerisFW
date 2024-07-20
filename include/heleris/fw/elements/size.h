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
HRSSize hrssz_create(const int width, const int height);

/*
 * Compare two sizes and return if are equals
 */
bool hrssz_equals(const HRSSize size1, const HRSSize size2);

/*
 * Return the area of a size
 */
int hrssz_area(const HRSSize size); 

/*
 * Scale a size (aka uniform multiplication)
 */
HRSSize hrssz_scale(const HRSSize size, const float scale);

/*
 * Convert to a string
 */
string_t hrssz_toString(const HRSSize size);

#endif