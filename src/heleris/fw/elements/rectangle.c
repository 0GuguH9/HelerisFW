#include "heleris/fw/elements/rectangle.h"

#include <string.h>

HRSRectangle hrsrec_create(const HRSVector2 pos, const HRSSize _size) {

    HRSRectangle rectangle = {pos, _size};
    return rectangle;
}

bool hrsrec_contains(const HRSRectangle rectangle, const HRSVector2 vector) {

    return (rectangle.position.x >= vector.x && (rectangle.position.x + rectangle._size.width) <= vector.x)
        && (rectangle.position.y >= vector.y && (rectangle.position.y + rectangle._size.height) <= vector.y);
}

bool hrsrec_intersect(const HRSRectangle rectangle1, const HRSRectangle rectangle2) {

    return ((rectangle1.position.x + rectangle1._size.width) >= rectangle2.position.x || rectangle1.position.x <= (rectangle2.position.x + rectangle2._size.width))
        && ((rectangle1.position.y + rectangle1._size.height) >= rectangle2.position.y || rectangle1.position.y <= (rectangle2.position.y + rectangle2._size.height));
}

string_t hrsrec_toString(const HRSRectangle _rectangle) {

    char buffer[125];
    snprintf(buffer, sizeof(buffer), "{Pos: %s, Size: %s}", hrsvc2_toString(_rectangle.position), hrssz_toString(_rectangle._size));

    return strdup(buffer);
}
