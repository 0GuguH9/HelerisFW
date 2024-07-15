#ifndef HELERIS_ELEMENTS_VECTOR_2_H
#define HELERIS_ELEMENTS_VECTOR_2_H

#include "../types.h"

// Represents a point in a 2D space
typedef struct HRSVector2 {
    float x;
    float y;
} HRSVector2;

/*
 * Create a vector
 */
HRSVector2 hrsvc2_create(float x, float y);

/*
 * Lenght of a vector
 */
float hrsvc2_length(HRSVector2 vector);

/*
 * Normalize a vector, aka making with lenght 1
 */
void hrsvc2_normalize(HRSVector2 vector);

/*
 * Add a vector by another
 */
HRSVector2 hrsvc2_add(HRSVector2 addend, HRSVector2 augend);

/*
 * Subtract a vector by another
 */
HRSVector2 hrsvc2_subtract(HRSVector2 minuend, HRSVector2 subtrahend);

/*
 * Divide a vector by a float.
 * Avoid for positions, use for sets of floats or velocities.
 */
HRSVector2 hrsvc2_fdivide(HRSVector2 dividend, float divisor);

/*
 * Divide a vector by another vector.
 * Avoid for positions, use for sets of floats or velocities.
 */
HRSVector2 hrsvc2_divide(HRSVector2 dividend, HRSVector2 divisor);

/*
 * Scale a vector by a uniform scale.
 * Avoid for positions, use for sets of floats or velocities.
 */
HRSVector2 hrsvc2_scale(HRSVector2 vector, float scalar);

/*
 * Scale a vector by a non-uniform scale, aka multiply.
 * Avoid for positions, use for sets of floats or velocities.
 */
HRSVector2 hrsvc2_multiply(HRSVector2 multiplicand, HRSVector2 multiplier);

/*
 * Distance from a vector to another (in 2D space)
 */
float hrsvc2_distance(HRSVector2 vector1, HRSVector2 vector2);

/*
 * Convert to a string
 */
string_t hrsvc2_toString(HRSVector2 vector);

#endif