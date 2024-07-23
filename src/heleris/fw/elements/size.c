#include "heleris/fw/elements/size.h"

#include <string.h>

HRSSize hrssz_create(const int width, const int height) {
    
    HRSSize _size = {width, height};
    return _size;
}

bool hrssz_equals(const HRSSize size1, const HRSSize size2) {
    return size1.width == size2.width && size1.height == size2.height;
}

int hrssz_area(const HRSSize _size) {
    return _size.width * _size.height;
}

HRSSize hrssz_scale(const HRSSize _size, const float scale) {
    HRSSize result = { (int)(_size.width * scale), (int)(_size.height * scale) };
    return result;
}

string_t hrssz_toString(const HRSSize _size) {

    char buffer[50];
    snprintf(buffer, sizeof(buffer), "{Width: %d, Height: %d}", _size.width, _size.height);

    return strdup(buffer);
}
