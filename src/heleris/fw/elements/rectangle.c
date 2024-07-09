#include "heleris/fw/elements/rectangle.h"

HRSRectangle hrsrec_create(HRSVector2 pos, HRSSize size) {

    HRSRectangle rectangle = {pos, size};
    return rectangle;
}

bool_t hrsrec_contains(HRSRectangle rectangle, HRSVector2 vector) {

    return (rectangle.position.x >= vector.x && (rectangle.position.x + rectangle.size.width) <= vector.x)
        && (rectangle.position.y >= vector.y && (rectangle.position.y + rectangle.size.height) <= vector.y);
}

bool_t hrsrec_intersect(HRSRectangle rectangle1, HRSRectangle rectangle2) {

    return ((rectangle1.position.x + rectangle1.size.width) >= rectangle2.position.x || rectangle1.position.x <= (rectangle2.position.x + rectangle2.size.width))
        && ((rectangle1.position.y + rectangle1.size.height) >= rectangle2.position.y || rectangle1.position.y <= (rectangle2.position.y + rectangle2.size.height));
}
