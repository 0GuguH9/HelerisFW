#include "heleris/fw/elements/vector3.h"

#include <math.h>
#include <string.h>

HRSVector3 hrsvc3_create(const float x, const float y, const float z) {

    HRSVector3 vector = {x, y, z};
    return vector;
}

float hrsvc3_length(const HRSVector3 vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

void hrsvc3_normalize(HRSVector3 vector) {

    float length = hrsvc3_length(vector);

    if (length != 0) {
        vector.x /= length;
        vector.y /= length;
        vector.z /= length;
    }
}

void hrsvc3_fastNormalize(HRSVector3 vector) {
    float length = hrsvc3_length(vector);

    if (length != 0.0f) {

        float inv_length;

        uint32_t i = *(uint32_t *)&length;
        i = 0x5f3759df - (i >> 1);
        inv_length = *(float *)&i;

        inv_length = inv_length * (1.5f - 0.5f * length * inv_length * inv_length);
        inv_length = inv_length * (1.5f - 0.5f * length * inv_length * inv_length);
        inv_length = inv_length * (1.5f - 0.5f * length * inv_length * inv_length);

        vector.x *= inv_length;
        vector.y *= inv_length;
        vector.z *= inv_length;
    }
}

HRSVector3 hrsvc3_add(const HRSVector3 addend, const HRSVector3 augend) {

    HRSVector3 result = { addend.x + augend.x, addend.y + augend.y , addend.z + augend.z };

    return result;
}

HRSVector3 hrsvc3_subtract(const HRSVector3 minuend, const HRSVector3 subtrahend) {

    HRSVector3 result = { minuend.x - subtrahend.x, minuend.y - subtrahend.y, minuend.z - subtrahend.z };

    return result;
}

HRSVector3 hrsvc3_fdivide(const HRSVector3 dividend, const float divisor) {

    HRSVector3 result = { dividend.x / divisor, dividend.y / divisor, dividend.z / divisor };

    return result;
}

HRSVector3 hrsvc3_divide(const HRSVector3 dividend, const HRSVector3 divisor) {

    HRSVector3 result = { dividend.x / divisor.x, dividend.y / divisor.y, dividend.z / divisor.z };

    return result;
}

HRSVector3 hrsvc3_scale(const HRSVector3 vector, const float scalar) {

    HRSVector3 result = { vector.x * scalar, vector.y * scalar, vector.z * scalar };

    return result;
}

HRSVector3 hrsvc3_multiply(const HRSVector3 multiplicand, const HRSVector3 multiplier) {

    HRSVector3 result = { multiplicand.x * multiplier.x, multiplicand.y * multiplier.y, multiplicand.z * multiplier.z };

    return result;
}

float hrsvc3_distance(const HRSVector3 vector1, const HRSVector3 vector2) {

    float dx = vector1.x - vector2.x;
    float dy = vector1.y - vector2.y;
    float dz = vector1.z - vector2.z;

    return sqrt(dx * dx + dy * dy + dz * dz);
}

string_t hrsvc3_toString(const HRSVector3 vector) {

    char buffer[125];
    snprintf(buffer, sizeof(buffer), "{X: %f, Y: %f, Z: %f}\n", vector.x, vector.y, vector.z);

    return strdup(buffer);
}
