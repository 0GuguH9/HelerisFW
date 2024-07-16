#ifndef HELERIS_MATH_H
#define HELERIS_MATH_H

#define HRS_MIN(a, b) (a < b ? a : b)

#define HRS_MAX(a, b) (a > b ? a : b)

#define HRS_SWAP(a, b) { \
    var temp = a; \
        a = b; \
        b = temp; \
    } \

#endif