#include "heleris/fw/elements/vector2.h"

#include <math.h>
#include <string.h>

HRSVector2 hrsvc2_create(float x, float y) {

    HRSVector2 vector = {x, y};
    return vector;
}

float hrsvc2_length(HRSVector2 vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

void hrsvc2_normalize(HRSVector2 vector) {

    float length = hrsvc2_length(vector);

    if (length != 0) {
        vector.x /= length;
        vector.y /= length;
    }
}

HRSVector2 hrsvc2_add(HRSVector2 addend, HRSVector2 augend) {

    HRSVector2 result = { addend.x + augend.x, addend.y + augend.y };

    return result;
}

HRSVector2 hrsvc2_subtract(HRSVector2 minuend, HRSVector2 subtrahend) {

    HRSVector2 result = { minuend.x - subtrahend.x, minuend.y - subtrahend.y };

    return result;
}

HRSVector2 hrsvc2_fdivide(HRSVector2 dividend, float divisor) {

    HRSVector2 result = { dividend.x / divisor, dividend.y / divisor };

    return result;
}

HRSVector2 hrsvc2_divide(HRSVector2 dividend, HRSVector2 divisor) {

    HRSVector2 result = { dividend.x / divisor.x, dividend.y / divisor.y };

    return result;
}

HRSVector2 hrsvc2_scale(HRSVector2 vector, float scalar) {

    HRSVector2 result = { vector.x * scalar, vector.y * scalar };

    return result;
}

HRSVector2 hrsvc2_multiply(HRSVector2 multiplicand, HRSVector2 multiplier) {

    HRSVector2 result = { multiplicand.x * multiplier.x, multiplicand.y * multiplier.y };

    return result;
}

float hrsvc2_distance(HRSVector2 vector1, HRSVector2 vector2) {

    float dx = vector1.x - vector2.x;
    float dy = vector1.y - vector2.y;

    return sqrt(dx * dx + dy * dy);
}

string_t hrsvc2_toString(HRSVector2 vector) {

    char buffer[75];
    snprintf(buffer, sizeof(buffer), "{X: %f, Y: %f}\n", vector.x, vector.y);

    return strdup(buffer);
}
