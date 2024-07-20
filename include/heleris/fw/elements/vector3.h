#ifndef HELERIS_ELEMENTS_VECTOR_3_H
#define HELERIS_ELEMENTS_VECTOR_3_H

#include "../types.h"

// Represents a point in a 3D space
typedef struct HRSVector3 {
    float x;
    float y;
    float z;
} HRSVector3;

/*
 * Create a vector
 */
HRSVector3 hrsvc3_create(const float x, const float y, const float z);

/*
 * Lenght of a vector
 */
float hrsvc3_length(const HRSVector3 vector);

/*
 * Normalize a vector, aka making with lenght 1
 */
void hrsvc3_normalize(HRSVector3 vector);

/*
 * Normalize a vector, aka making with lenght 1, in a fast way, but no too precise.
 */
void hrsvc3_fastNormalize(HRSVector3 vector);

/*
 * Add a vector by another
 */
HRSVector3 hrsvc3_add(const HRSVector3 addend, const HRSVector3 augend);

/*
 * Subtract a vector by another
 */
HRSVector3 hrsvc3_subtract(const HRSVector3 minuend, const HRSVector3 subtrahend);

/*
 * Divide a vector by a float.
 * Avoid for positions, use for sets of floats or velocities.
 */
HRSVector3 hrsvc3_fdivide(const HRSVector3 dividend, const float divisor);

/*
 * Divide a vector by another vector.
 * Avoid for positions, use for sets of floats or velocities.
 */
HRSVector3 hrsvc3_divide(const HRSVector3 dividend, const HRSVector3 divisor);

/*
 * Scale a vector by a uniform scale.
 * Avoid for positions, use for sets of floats or velocities.
 */
HRSVector3 hrsvc3_scale(const HRSVector3 vector, const float scalar);

/*
 * Scale a vector by a non-uniform scale, aka multiply.
 * Avoid for positions, use for sets of floats or velocities.
 */
HRSVector3 hrsvc3_multiply(const HRSVector3 multiplicand, const HRSVector3 multiplier);


/*
 * Distance from a vector to another (in 3D space)
 */
float hrsvc3_distance(const HRSVector3 vector1, const HRSVector3 vector3);

/*
 * Convert to a string
 */
string_t hrsvc3_toString(const HRSVector3 vector);

#endif