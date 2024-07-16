#include "heleris/fw/elements/rectangle.h"

#include <string.h>

HRSRectangle hrsrec_create(HRSVector2 pos, HRSSize size) {

    HRSRectangle rectangle = {pos, size};
    return rectangle;
}

bool hrsrec_contains(HRSRectangle rectangle, HRSVector2 vector) {

    return (rectangle.position.x >= vector.x && (rectangle.position.x + rectangle.size.width) <= vector.x)
        && (rectangle.position.y >= vector.y && (rectangle.position.y + rectangle.size.height) <= vector.y);
}

bool hrsrec_intersect(HRSRectangle rectangle1, HRSRectangle rectangle2) {

    return ((rectangle1.position.x + rectangle1.size.width) >= rectangle2.position.x || rectangle1.position.x <= (rectangle2.position.x + rectangle2.size.width))
        && ((rectangle1.position.y + rectangle1.size.height) >= rectangle2.position.y || rectangle1.position.y <= (rectangle2.position.y + rectangle2.size.height));
}

string_t hrsrec_toString(HRSRectangle rectangle) {

    char buffer[125];
    snprintf(buffer, sizeof(buffer), "{Pos: %s, Size: %s}", hrsvc2_toString(rectangle.position), hrssz_toString(rectangle.size));

    return strdup(buffer);
}
