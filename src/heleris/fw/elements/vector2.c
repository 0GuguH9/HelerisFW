#include "heleris/fw/elements/vector2.h"

#include <math.h>
#include <string.h>

HRSVector2 hrsvc2_create(const float x, const float y) {

    HRSVector2 vector = {x, y};
    return vector;
}

float hrsvc2_length(const HRSVector2 vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

void hrsvc2_normalize(HRSVector2 vector) {

    float length = hrsvc2_length(vector);

    if (length != 0) {
        vector.x /= length;
        vector.y /= length;
    }
}

HRSVector2 hrsvc2_add(const HRSVector2 addend, const HRSVector2 augend) {

    HRSVector2 result = { addend.x + augend.x, addend.y + augend.y };

    return result;
}

HRSVector2 hrsvc2_subtract(const HRSVector2 minuend, const HRSVector2 subtrahend) {

    HRSVector2 result = { minuend.x - subtrahend.x, minuend.y - subtrahend.y };

    return result;
}

HRSVector2 hrsvc2_fdivide(const HRSVector2 dividend, const float divisor) {

    HRSVector2 result = { dividend.x / divisor, dividend.y / divisor };

    return result;
}

HRSVector2 hrsvc2_divide(const HRSVector2 dividend, const HRSVector2 divisor) {

    HRSVector2 result = { dividend.x / divisor.x, dividend.y / divisor.y };

    return result;
}

HRSVector2 hrsvc2_scale(const HRSVector2 vector, const float scalar) {

    HRSVector2 result = { vector.x * scalar, vector.y * scalar };

    return result;
}

HRSVector2 hrsvc2_multiply(const HRSVector2 multiplicand, const HRSVector2 multiplier) {

    HRSVector2 result = { multiplicand.x * multiplier.x, multiplicand.y * multiplier.y };

    return result;
}

float hrsvc2_distance(const HRSVector2 vector1, const HRSVector2 _vector2) {

    float dx = vector1.x - _vector2.x;
    float dy = vector1.y - _vector2.y;

    return sqrt(dx * dx + dy * dy);
}

string_t hrsvc2_toString(const HRSVector2 vector) {

    char buffer[75];
    snprintf(buffer, sizeof(buffer), "{X: %f, Y: %f}", vector.x, vector.y);

    return strdup(buffer);
}
