#ifndef HELERIS_ELEMENTS_RECTANGLE_H
#define HELERIS_ELEMENTS_RECTANGLE_H

#include "size.h"
#include "vector2.h"

typedef struct HRSRectangle {
    HRSVector2 position;
    HRSSize size;
} HRSRectangle;

HRSRectangle hrsrec_create(HRSVector2 pos, HRSSize size);

bool_t hrsrec_contains(HRSRectangle rectangle, HRSVector2 vector);

bool_t hrsrec_intersect(HRSRectangle rectangle1, HRSRectangle rectangle2);

#endif