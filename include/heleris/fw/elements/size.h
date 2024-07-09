#ifndef HELERIS_ELEMENTS_SIZE_2_H
#define HELERIS_ELEMENTS_SIZE_2_H

#include "../types.h"

typedef struct HRSSize {
    int width;
    int height;
} HRSSize;

HRSSize hrssz_create(int width, int height);

bool_t hrssz_equals(HRSSize size1, HRSSize size2);

int hrssz_area(HRSSize size); 

HRSSize hrssz_scale(HRSSize size, float scale);

string_t hrssz_toString(HRSSize size);

#endif