#include "heleris/fw/elements/size2.h"

#include <string.h>

bool_t hrssize2_equals(HRSSize2 s1, HRSSize2 s2) {
    return s1.width == s2.width && s1.height == s2.height;
}

int hrssize2_area(HRSSize2 size) {
    return size.width * size.height;
}

HRSSize2 hrssize2_scale(HRSSize2 size, float scale) {
    HRSSize2 result = { (int)(size.width * scale), (int)(size.height * scale) };
    return result;
}

string_t hrssz2_toString(HRSSize2 size) {

    char buffer[50];
    snprintf(buffer, sizeof(buffer), "{Width: %d, Height: %d}\n", size.width, size.height);

    return strdup(buffer);
}
