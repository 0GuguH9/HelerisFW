#ifndef HELERIS_ELEMENTS_SIZE_2_H
#define HELERIS_ELEMENTS_SIZE_2_H

typedef struct HRSSize2 {
    int width;
    int height;
} HRSSize2;

HRSSize2 hrssz2_create(int width, int height);

#endif