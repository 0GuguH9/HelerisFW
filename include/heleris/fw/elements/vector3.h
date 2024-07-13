#ifndef HELERIS_ELEMENTS_VECTOR_3_H
#define HELERIS_ELEMENTS_VECTOR_3_H

#include "../types.h"

typedef struct HRSVector3 {
    float x;
    float y;
    float z;
} HRSVector3;

/*
 * Create a vector
 */
HRSVector3 hrsvc3_create(float x, float y, float z);

/*
 * Lenght of a vector
 */
float hrsvc3_length(HRSVector3 vector);

/*
 * Normalize a vector, aka making with lenght 1
 */
void hrsvc3_normalize(HRSVector3 vector);

/*
 * Add a vector by another
 */
HRSVector3 hrsvc3_add(HRSVector3 addend, HRSVector3 augend);

/*
 * Subtract a vector by another
 */
HRSVector3 hrsvc3_subtract(HRSVector3 minuend, HRSVector3 subtrahend);

/*
 * Divide a vector by a float.
 * Avoid for positions, use for sets of floats or velocities.
 */
HRSVector3 hrsvc3_fdivide(HRSVector3 dividend, float divisor);

/*
 * Divide a vector by another vector.
 * Avoid for positions, use for sets of floats or velocities.
 */
HRSVector3 hrsvc3_divide(HRSVector3 dividend, HRSVector3 divisor);

/*
 * Scale a vector by a uniform scale.
 * Avoid for positions, use for sets of floats or velocities.
 */
HRSVector3 hrsvc3_scale(HRSVector3 vector, float scalar);

/*
 * Scale a vector by a non-uniform scale, aka multiply.
 * Avoid for positions, use for sets of floats or velocities.
 */
HRSVector3 hrsvc3_multiply(HRSVector3 multiplicand, HRSVector3 multiplier);


/*
 * Distance from a vector to another (in 3D space)
 */
float hrsvc3_distance(HRSVector3 vector1, HRSVector3 vector3);

/*
 * Convert to a string
 */
string_t hrsvc3_toString(HRSVector3 vector);

#endif