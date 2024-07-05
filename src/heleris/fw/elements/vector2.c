#include "heleris/fw/elements/vector2.h"

#include <math.h>
#include <string.h>

float hrsvc2_magnitude(HRSVector2 vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

void hrsvc2_normalize(HRSVector2 vector) {

    float magnitude = hrsvc2_magnitude(vector);

    if (magnitude != 0) {
        vector.x /= magnitude;
        vector.y /= magnitude;
    }
}

HRSVector2 hrsvc2_add(HRSVector2 vector1, HRSVector2 vector2) {

    HRSVector2 result = { vector1.x + vector2.x, vector1.y + vector2.y };

    return result;
}

HRSVector2 hrsvc2_subtract(HRSVector2 vector1, HRSVector2 vector2) {

    HRSVector2 result = { vector1.x - vector2.x, vector1.y - vector2.y };

    return result;
}

HRSVector2 hrsvc2_multiply(HRSVector2 vector1, HRSVector2 vector2) {

    HRSVector2 result = { vector1.x * vector2.x, vector1.y * vector2.y };

    return result;
}

HRSVector2 hrsvc2_divide(HRSVector2 vector1, HRSVector2 vector2) {

    HRSVector2 result = { vector1.x / vector2.x, vector1.y / vector2.y };

    return result;
}

HRSVector2 hrsvc2_multiplyByScalar(HRSVector2 vector, float scalar) {

    HRSVector2 result = { vector.x * scalar, vector.y * scalar };

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
