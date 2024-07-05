#ifndef HELERIS_ELEMENTS_VECTOR_2_H
#define HELERIS_ELEMENTS_VECTOR_2_H

#include "../types.h"

typedef struct HRSVector2 {
    float x;
    float y;
} HRSVector2;

float hrsvc2_magnitude(HRSVector2 vector);

void hrsvc2_normalize(HRSVector2 vector);

HRSVector2 hrsvc2_add(HRSVector2 vector1, HRSVector2 vector2);

HRSVector2 hrsvc2_subtract(HRSVector2 vector1, HRSVector2 vector2);

HRSVector2 hrsvc2_multiply(HRSVector2 vector1, HRSVector2 vector2);

HRSVector2 hrsvc2_divide(HRSVector2 vector1, HRSVector2 vector2);

HRSVector2 hrsvc2_multiplyByScalar(HRSVector2 vector, float scalar);

float hrsvc2_distance(HRSVector2 vector1, HRSVector2 vector2);

string_t hrsvc2_toString(HRSVector2 vector);

#endif