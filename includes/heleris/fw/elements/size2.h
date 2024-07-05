#ifndef HELERIS_ELEMENTS_SIZE_2_H
#define HELERIS_ELEMENTS_SIZE_2_H

#include "../types.h"

typedef struct HRSSize2 {
    int width;
    int height;
} HRSSize2;

bool_t hrssize2_equals(HRSSize2 s1, HRSSize2 s2);

int hrssize2_area(HRSSize2 size); 

HRSSize2 hrssize2_scale(HRSSize2 size, float scale);

string_t hrssz2_toString(HRSSize2 size);

#endif