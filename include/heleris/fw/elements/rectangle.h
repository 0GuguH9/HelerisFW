#ifndef HELERIS_ELEMENTS_RECTANGLE_H
#define HELERIS_ELEMENTS_RECTANGLE_H

#include "size.h"
#include "vector2.h"

// Represents a retangle with a position and size
typedef struct HRSRectangle {
    HRSVector2 position;
    HRSSize size;
} HRSRectangle;

/*
 * Create a rectangle
 */
HRSRectangle hrsrec_create(HRSVector2 pos, HRSSize size);

/*
 * Return if the rectangle contains this position
 */
bool_t hrsrec_contains(HRSRectangle rectangle, HRSVector2 vector);

/*
 * Return if a rectangle intersect another
 */
bool_t hrsrec_intersect(HRSRectangle rectangle1, HRSRectangle rectangle2);

/*
 * Convert to a string
 */
string_t hrsrec_toString(HRSRectangle rectangle);

#endif