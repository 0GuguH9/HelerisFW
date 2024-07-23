#ifndef HELERIS_ELEMENTS_RECTANGLE_H
#define HELERIS_ELEMENTS_RECTANGLE_H

#include "size.h"
#include "vector2.h"

// Represents a retangle with a position and size
typedef struct HRSRectangle {
    HRSVector2 position;
    HRSSize _size;
} HRSRectangle;

/*
 * Create a rectangle
 */
HRSRectangle hrsrec_create(const HRSVector2 pos, const HRSSize _size);

/*
 * Return if the rectangle contains this position
 */
bool hrsrec_contains(const HRSRectangle _rectangle, const HRSVector2 vector);

/*
 * Return if a rectangle intersect another
 */
bool hrsrec_intersect(const HRSRectangle rectangle1, const HRSRectangle rectangle2);

/*
 * Convert to a string
 */
string_t hrsrec_toString(const HRSRectangle _rectangle);

#endif