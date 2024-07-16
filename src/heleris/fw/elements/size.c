#include "heleris/fw/elements/size.h"

#include <string.h>

HRSSize hrssz_create(int width, int height) {
    
    HRSSize size = {width, height};
    return size;
}

bool hrssz_equals(HRSSize size1, HRSSize size2) {
    return size1.width == size2.width && size1.height == size2.height;
}

int hrssz_area(HRSSize size) {
    return size.width * size.height;
}

HRSSize hrssz_scale(HRSSize size, float scale) {
    HRSSize result = { (int)(size.width * scale), (int)(size.height * scale) };
    return result;
}

string_t hrssz_toString(HRSSize size) {

    char buffer[50];
    snprintf(buffer, sizeof(buffer), "{Width: %d, Height: %d}", size.width, size.height);

    return strdup(buffer);
}
