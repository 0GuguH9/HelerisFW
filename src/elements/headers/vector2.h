#ifndef HELERIS_ELEMENTS_VECTOR_2_H
#define HELERIS_ELEMENTS_VECTOR_2_H

#include "../../types.h"

typedef struct HRSVector2 {
    float x;
    float y;
} HRSVector2;

HRSVector2 hrsvc2_create(float x, float y);

void hrsvc2_normalize(HRSVector2 *vector);

string_t hrsvc2_toString(HRSVector2 *vector);

#endif