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
HRSVector2 hrsvc2_create(const float x, const float y);

/*
 * Lenght of a vector
 */
float hrsvc2_length(const HRSVector2 vector);

/*
 * Normalize a vector, aka making with lenght 1
 */
void hrsvc2_normalize(HRSVector2 vector);

/*
 * Add a vector by another
 */
HRSVector2 hrsvc2_add(const HRSVector2 addend, const HRSVector2 augend);

/*
 * Subtract a vector by another
 */
HRSVector2 hrsvc2_subtract(const HRSVector2 minuend, const HRSVector2 subtrahend);

/*
 * Divide a vector by a float.
 * Avoid for positions, use for sets of floats or velocities.
 */
HRSVector2 hrsvc2_fdivide(const HRSVector2 dividend, const float divisor);

/*
 * Divide a vector by another vector.
 * Avoid for positions, use for sets of floats or velocities.
 */
HRSVector2 hrsvc2_divide(const HRSVector2 dividend, const HRSVector2 divisor);

/*
 * Scale a vector by a uniform scale.
 * Avoid for positions, use for sets of floats or velocities.
 */
HRSVector2 hrsvc2_scale(const HRSVector2 vector, const float scalar);

/*
 * Scale a vector by a non-uniform scale, aka multiply.
 * Avoid for positions, use for sets of floats or velocities.
 */
HRSVector2 hrsvc2_multiply(const HRSVector2 multiplicand, const HRSVector2 multiplier);

/*
 * Distance from a vector to another (in 2D space)
 */
float hrsvc2_distance(const HRSVector2 vector1, const HRSVector2 vector2);

/*
 * Convert to a string
 */
string_t hrsvc2_toString(const HRSVector2 vector);

#endif